#include <graphics/GraphicsEngine.hh>

#include <debug/Debug.hh>
#include <graphics/graphic_types.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <common/Status.hh>
#include <game/Cell.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <debug/OSD.hh>
#include <context/State.hh>
#include <chrono>



namespace graphics {

const sf::Color GRID_COLOR(202, 124, 0);


// Static Variables definition
std::unique_ptr<RenderWindow> GraphicsEngine::_window;
float GraphicsEngine::_currentFPS;


std::vector<long int> frames_generation;


void GraphicsEngine::drawScene(const std::shared_ptr<Battle> battle)
{
  std::chrono::steady_clock::time_point draw_start = std::chrono::steady_clock::now();

  drawBackground();
  drawMap(battle);

  // draw the interface of current_player
  drawGrid(battle->map());

  drawState();

  // draw the debug data, eventually over everything (at last)
  debug::OSD::addData(_currentFPS);
  debug::OSD::draw();
  ++_currentFPS;

  // update the window
  _window->display();

  auto draw_time(std::chrono::steady_clock::now() - draw_start);
  frames_generation.push_back(draw_time.count());

  if (frames_generation.size() % 60 == 0)
  {
    long int total_time = 0;
    for (const auto& it: frames_generation)
    {
      total_time += it;
    }

    PRINTF("time to generate 60 frames (ms):", total_time / 1000000);
    frames_generation.clear();
  }
}



void GraphicsEngine::drawState() {
  Status::currentState()->draw();
}


void GraphicsEngine::drawBackground()
{
  _window->clear();
  /// \todo draw map background
}


void GraphicsEngine::drawMap(const std::shared_ptr<Battle> battle)
{
  const std::shared_ptr<Map> map(battle->map());

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
      const std::shared_ptr<Cell> c = cells[col][line];

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
    rectangle.setSize({p::cellWidth(),
                       p::cellHeight() * static_cast<component> (map->nbLines())});

    _window->draw(rectangle);

    // skipping to next column
    offset_x += p::cellWidth(); /// \todo - grid thickness in x / 2
  }
}



void GraphicsEngine::drawUnit(const std::shared_ptr<Unit> unit)
{
  using p = MapGraphicsProperties;

  // image.sprite()->setColor(Status::player()->unitsColor());
  auto sprite(unit->sprite());
  auto x(sprite->getTexture()->getSize().x);
  auto y(sprite->getTexture()->getSize().y);
  sprite->setScale(p::cellWidth() / static_cast<component> (x),
                   p::cellHeight() / static_cast<component> (y));

# ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (x < p::cellWidth() || y < p::cellHeight()) {
    ERROR("Sprite scale failure");
  }
# endif

  auto players = Status::battle()->players();
  sprite->setColor(players[unit->playerId()]->color());

  if (unit->played()) {
    sprite->setColor(Color(127, 127, 127, 150));
  }

  unit->image()->drawAtCell(unit->coords());
}


void GraphicsEngine::drawInterface()
{
  auto interface(Status::interface());

  // Draw every interface elements related to the current context
  for (const auto& elt: interface->elements())
  {
    elt->update();
    elt->draw();
  }
}


void GraphicsEngine::setWindow(std::unique_ptr<RenderWindow> window) {
  _window = std::move(window);
}


void GraphicsEngine::setGridOffset(const std::shared_ptr<Map> map)
{
  using p = MapGraphicsProperties;

  // offset = 1/2 left room
  p::setGridOffsetX((static_cast<component> (_window->getSize().x) - p::cellWidth()
                     * static_cast<component> (map->nbColumns())) / 2);

  p::setGridOffsetY((static_cast<component> (_window->getSize().y) - p::cellHeight()
                     * static_cast<component> (map->nbLines())) / 2);
}



} // namespace graphics
