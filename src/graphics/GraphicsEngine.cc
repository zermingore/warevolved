/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \namespace graphics
 * \brief GraphicsEngine class definition
 */

#include <graphics/GraphicsEngine.hh>

#include <chrono>
#include <ctime> // strftime

#include <context/State.hh>
#include <debug/Debug.hh>
#include <debug/OSD.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <graphics/graphic_types.hh>
#include <input/EventsProcessor.hh>
#include <interface/Interface.hh>
#include <tools/Fps.hh>



namespace graphics {

const sf::Color GRID_COLOR(202, 124, 0);

// Static Variables definition
std::unique_ptr<RenderWindow> GraphicsEngine::_window;
bool GraphicsEngine::_takeScreenshot;
bool GraphicsEngine::_exit;
std::unique_ptr<TerrainsHandler> GraphicsEngine::_terrainsHandler;



void GraphicsEngine::drawScene(const std::shared_ptr<Battle>& battle)
{
  _window->setActive();
  _exit = false;
  _takeScreenshot = false;
  _terrainsHandler = std::make_unique<TerrainsHandler> ();
  setGridOffset(battle->map());

  using namespace std::chrono;
  while (_window->isOpen() && !_exit)
  {
    auto graphics_start(steady_clock::now());
    drawBackground();
    drawMap(battle);

    // draw the interface of current_player
    drawGrid(battle->map());

    drawState();
    drawInterface();

    // Handle screenshot request, if any
    if (_takeScreenshot) {
      screenshot();
    }

    duration<double> time_elapsed = steady_clock::now() - graphics_start;
    tools::Fps::updateFps(time_elapsed.count());

    // draw the debug data, eventually over everything (at last)
    debug::OSD::draw();

    // update the window
    _window->display();

    EventsProcessor::notifyFrame();
  }

  WARNING("Quitting War Evolved");
}



void GraphicsEngine::drawState()
{
  game::Status::drawState();
}



void GraphicsEngine::screenshot()
{
  // Build the screenshot file name with the date
  time_t now = time(nullptr);
  tm *date = localtime(&now);
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


void GraphicsEngine::drawMap(const std::shared_ptr<Battle>& battle)
{
  const auto map(battle->map());

  // drawing cells (their background and their content)
  const auto cells(map->cells());

  // draw column by column (as the cells are stored by column)
  for (auto col(0u); col < map->nbColumns(); ++col)
  {
    for (auto line(0u); line < map->nbLines(); ++line)
    {
      /// \todo check if we print the cell (scroll case)
      const auto c { cells[col][line] };
      auto terrain(TerrainsHandler::get(c->terrain()));
      graphics::Sprite img(terrain.texture());
      img.drawAtCell(c->coords());

      if (c->highlight())
      {
        auto highlight = std::make_shared<Sprite> ("highlight");
        highlight->setColor(c->highlightColor());
        highlight->drawAtCell(c->coords());
      }

      if (c->unit()) {
        drawUnit(c->unit());
      }
    }
  }
}



void GraphicsEngine::drawGrid(const std::shared_ptr<Map>& map)
{
  using p = graphics::Properties;

  // Lines
  auto offset_y(p::gridOffsetY());
  const auto len = p::cellWidth() * static_cast<component> (map->nbColumns())
    + p::gridThickness();
  RectangleShape line({len, p::gridThickness()});
  line.setFillColor(GRID_COLOR);
  for (auto l(0u); l <= map->nbLines(); ++l)
  {
    line.setPosition(p::gridOffsetX(), offset_y);
    _window->draw(line);
    offset_y += p::cellHeight();
  }

  // Columns
  auto offset_x(p::gridOffsetX());
  const auto height = p::cellHeight() * static_cast<component> (map->nbLines())
    + p::gridThickness();
  RectangleShape col({p::gridThickness(), height});
  col.setFillColor(GRID_COLOR);
  for (auto c(0u); c <= map->nbColumns(); ++c)
  {
    col.setPosition(offset_x, p::gridOffsetY());
    _window->draw(col);
    offset_x += p::cellWidth();
  }
}



void GraphicsEngine::drawUnit(const std::shared_ptr<Unit>& unit)
{
  using p = graphics::Properties;

  // image.sprite()->setColor(game::Status::player()->unitsColor());
  auto sprite(unit->sprite());
  auto x(sprite->texture()->getSize().x);
  auto y(sprite->texture()->getSize().y);
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

  auto players = game::Status::battle()->players();
  sprite->setColor(players[unit->playerId()]->color());

  if (unit->played()) {
    sprite->setColor(Color(127, 127, 127, 150));
  }

  unit->sprite()->drawAtCell(unit->coords());
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



void GraphicsEngine::setGridOffset(const std::shared_ptr<const Map>& map)
{
  using p = graphics::Properties;
  using components = const std::pair<const component, const component>;

  // offset = 1/2 left room
  components size {_window->getSize().x, _window->getSize().y};
  components dims {map->nbColumns(), map->nbLines()};
  p::setGridOffsetX((size.first  - p::cellWidth()  * dims.first)  / 2);
  p::setGridOffsetY((size.second - p::cellHeight() * dims.second) / 2);
}



void GraphicsEngine::resizeWindow(unsigned int width, unsigned int height)
{
  _window->setView(sf::View( {
    0, 0, static_cast<float> (width), static_cast<float> (height)
  }));

  // Re-center the map
  auto battle{game::Status::battle()};
  setGridOffset(battle->map());

  // Update panel position
  for (auto player: battle->players())
  {
    player->updatePanelPosition({ static_cast<float> (width),
                                  static_cast<float> (height) });
  }
}



void GraphicsEngine::exitRequest()
{
  _exit = true; // Terminate the 'DrawScene' thread

  // NOT closing the window in order to prevent the event thread from crashing

  // Terminate the main thread; Nothing will try to catch it
  throw std::runtime_error("Exiting War Evolved");
}



} // namespace graphics
