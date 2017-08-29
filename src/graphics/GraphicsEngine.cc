#include <graphics/GraphicsEngine.hh>

#include <chrono>
#include <ctime> // strftime

#include <debug/Debug.hh>
#include <debug/OSD.hh>
#include <graphics/graphic_types.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <interface/Interface.hh>
#include <game/Status.hh>
#include <game/Cell.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <context/State.hh>



namespace graphics {

const sf::Color GRID_COLOR(202, 124, 0);


// Static Variables definition
std::unique_ptr<RenderWindow> GraphicsEngine::_window;
size_t GraphicsEngine::_nbFramesGenerated;
bool GraphicsEngine::_takeScreenshot;


constexpr double computeFps(size_t nb_frames, long int ns_elapsed)
{
  return (  static_cast<float> (nb_frames)
          / static_cast<float> (ns_elapsed) * 1000000000.f);
}


void GraphicsEngine::drawScene(const std::shared_ptr<Battle> battle)
{
  _window->setActive();
  _takeScreenshot = false;
  while (_window->isOpen())
  {
    static auto graphics_start(std::chrono::steady_clock::now());

    auto draw_start(std::chrono::steady_clock::now());
    drawBackground();
    drawMap(battle);

    // draw the interface of current_player
    drawGrid(battle->map());

    drawState();

    // draw the debug data, eventually over everything (at last)
    ++_nbFramesGenerated;
    auto time_elapsed(std::chrono::steady_clock::now() - graphics_start);
    debug::OSD::addPod(computeFps(_nbFramesGenerated, time_elapsed.count()),
                       "FPS (from nb generated frames)");
    debug::OSD::draw();

    // Handle screenshot request, if any
    if (_takeScreenshot)
    {
        screenshot();
    }

    // update the window
    _window->display();
  }
}


void GraphicsEngine::drawState()
{
  game::Status::currentState()->draw();
}


void GraphicsEngine::screenshot()
{
  // Build the screenshot file name with the date
  time_t now = time(nullptr);
  struct tm *date = localtime(&now);
  char path[80] = {0};
  strftime(path, 80, "/tmp/./we_screenshot__%Y_%m_%d__%H_%M_%S.png", date);

  // Get the screenshot
  NOTICE("screenshot: getting image");
  auto size {_window->getSize()};
  Texture texture;
  texture.create(size.x, size.y);
  texture.update(*_window);
  auto image {texture.copyToImage()};

  // Save the image to a file
  if (!image.saveToFile(path))
  {
    ERROR("Unable to save the screenshot; given path: ", path);
    return;
  }

  NOTICE("Screenshot saved as", path);

  _takeScreenshot = false;
}



void GraphicsEngine::drawBackground()
{
  _window->clear();
  /// \todo draw map background
}


void GraphicsEngine::drawMap(const std::shared_ptr<Battle> battle)
{
  const auto map(battle->map());

  // re-checking grid offsets
  setGridOffset(map);

  // drawing cells (their background and their content)
  const auto cells(map->cells());

  /// \todo [Optimization] fetch every terrain first
  /// (but not here, in MapGraphicsProperties ?)

  // draw column by column (as the cells are stored by column)
  for (auto col(0u); col < map->nbColumns(); ++col)
  {
    for (auto line(0u); line < map->nbLines(); ++line)
    {
      /// \todo check if we print the cell (scroll case)
      const auto c {cells[col][line]};
      switch (c->terrain())
      {
        default:
          auto img(resources::ResourcesManager::getImage("forest"));
          img->drawAtCell(c->coords());
          break;
      }

      if (c->highlight())
      {
        auto highlight = resources::ResourcesManager::getImage("highlight");
        highlight->sprite()->setColor(c->highlightColor());
        highlight->drawAtCell(c->coords());
      }

      if (c->unit()) {
        drawUnit(c->unit());
      }
    }
  }
}



void GraphicsEngine::drawGrid(const std::shared_ptr<Map> map)
{
  RectangleShape rectangle;
  rectangle.setFillColor(Color::Transparent);
  rectangle.setOutlineColor(GRID_COLOR);
  rectangle.setOutlineThickness(MapGraphicsProperties::gridThickness());


  // for each line, draw a rectangle
  using p = MapGraphicsProperties;
  auto offset_x(p::gridOffsetX());
  auto offset_y(p::gridOffsetY());
  for (auto i(0u); i < map->nbLines(); ++i)
  {
    rectangle.setPosition(offset_x, offset_y);

    rectangle.setSize({
        p::cellWidth() * static_cast<component> (map->nbColumns()),
        p::cellHeight()});

    _window->draw(rectangle);

    // skipping to next line
    offset_y += p::cellHeight(); /// \todo - grid thickness in y / 2
  }


  // for each column draw a rectangle
  // resetting offsets
  offset_x = p::gridOffsetX();
  offset_y = p::gridOffsetY();
  for (auto col(0u); col < map->nbColumns(); ++col)
  {
    rectangle.setPosition(offset_x, offset_y);
    rectangle.setSize(
      {p::cellWidth(),
       p::cellHeight() * static_cast<component> (map->nbLines())});

    _window->draw(rectangle);

    // skipping to next column
    offset_x += p::cellWidth(); /// \todo - grid thickness in x / 2
  }
}



void GraphicsEngine::drawUnit(const std::shared_ptr<Unit> unit)
{
  using p = MapGraphicsProperties;

  // image.sprite()->setColor(game::Status::player()->unitsColor());
  auto sprite(unit->sprite());
  auto x(sprite->getTexture()->getSize().x);
  auto y(sprite->getTexture()->getSize().y);
  sprite->setScale(p::cellWidth()  / static_cast<component> (x),
                   p::cellHeight() / static_cast<component> (y));

# ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (   static_cast<component> (x) < p::cellWidth()
      || static_cast<component> (y) < p::cellHeight())
  {
    ERROR("Sprite scale failure");
  }
# endif

  auto players {game::Status::battle()->players()};
  sprite->setColor(players[unit->playerId()]->color());

  if (unit->played()) {
    sprite->setColor(Color(127, 127, 127, 150));
  }

  unit->image()->drawAtCell(unit->coords());
}


void GraphicsEngine::drawInterface()
{
  auto interface(game::Status::interface());

  // Draw every interface elements related to the current context
  for (const auto& elt: interface->elements())
  {
    elt->update();
    elt->draw();
  }
}


void GraphicsEngine::setGridOffset(const std::shared_ptr<const Map> map)
{
  using p = MapGraphicsProperties;
  using components = const std::pair<const component, const component>;

  // offset = 1/2 left room
  components size {_window->getSize().x, _window->getSize().y};
  components dims {map->nbColumns(), map->nbLines()};
  p::setGridOffsetX((size.first  - p::cellWidth()  * dims.first)  / 2);
  p::setGridOffsetY((size.second - p::cellHeight() * dims.second) / 2);
}


} // namespace graphics
