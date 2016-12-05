#include <graphics/GraphicsEngine.hh>
#include <common/constants.hh> // GRID_COLOR
#include <common/Status.hh>
#include <game/Cell.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>


namespace graphics {

// Static Variables definition
std::unique_ptr<sf::RenderWindow> GraphicsEngine::_window;
float GraphicsEngine::_currentFPS;


void GraphicsEngine::drawScene(const std::shared_ptr<Battle> battle)
{
  drawBackground();

  // battle->map()->update();
  drawMap(battle);
  drawGrid(battle->map());

  // unit selection managed by the interface ?
  //   interface / player can do everything
  //   when done, call map to check and do the move / attack

  // study (broken ATM)
  // pf: left -> push, right -> pop ...
  // 1 2 4 8 -> 0001 & 0001 -> push / pop
  // left 0001 0010 right


  // draw interface of current_player
  drawInterface(battle);

  // update the window
  _window->display();
}


void GraphicsEngine::drawInterface(const std::shared_ptr<Battle> battle)
{
  auto interface(Status::interface());

  // Draw every interface elements related to the current context
  for (const auto& elt: interface->elements())
  {
    elt->update(battle->map()->graphicsProperties());
    elt->draw();

    /// \todo OSD debug infos
    auto font(resources::ResourcesManager::getFont("font_army"));
    auto label(std::make_shared<sf::Text> ());
    label->setFont(*(font.getFont()));
    char test(interface->elements().size() + 48); // C-style ...
    label->setString(test);
    draw(label);
  }
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


  // draw line by line
  for (auto i(0u); i < map->nbLines(); ++i)
  {
    for (auto j(0u); j < map->nbColumns(); ++j)
    {
      /// \todo check if we print the cell (scroll case)
      const std::shared_ptr<Cell> c = cells[i][j];

      switch (c->terrain())
      {
        default:
          auto img(resources::ResourcesManager::getImage("forest"));
          img.drawAtCell(c->coords(), map->graphicsProperties());
          break;
      }

      if (c->highlight())
      {
        Image& highlight = resources::ResourcesManager::getImage("highlight");
        highlight.sprite()->setColor(c->highlightColor());
        highlight.drawAtCell(c->coords(), map->graphicsProperties());
      }

      if (c->unit()) {
        drawUnit(battle, c->unit());
      }
    }
  }
}



void GraphicsEngine::drawGrid(const std::shared_ptr<Map> map)
{
  auto p(map->graphicsProperties());
  sf::RectangleShape rectangle;
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(GRID_COLOR);
  rectangle.setOutlineThickness(p->gridThickness());


  // for each line, draw a rectangle
  auto offset_x(p->gridOffsetX());
  auto offset_y(p->gridOffsetY());
  for (auto i(0u); i < map->nbLines(); ++i)
  {
    rectangle.setPosition(offset_x, offset_y);
    rectangle.setSize(sf::Vector2f(p->cellWidth() * map->nbColumns(),
                                   p->cellHeight()));

    _window->draw(rectangle);

    // skipping to next line
    offset_y += p->cellHeight(); /// \todo - grid thickness in y / 2
  }


  // for each column draw a rectangle
  // resetting offsets
  offset_x = p->gridOffsetX();
  offset_y = p->gridOffsetY();
  for (auto j(0u); j < map->nbColumns(); ++j)
  {
    rectangle.setPosition(offset_x, offset_y);
    rectangle.setSize(sf::Vector2f(p->cellWidth(),
                                   p->cellHeight() * map->nbLines()));

    _window->draw(rectangle);

    // skipping to next column
    offset_x += p->cellWidth(); /// \todo - grid thickness in x / 2
  }
}



void GraphicsEngine::drawUnit(const std::shared_ptr<Battle> battle,
                              const std::shared_ptr<Unit> unit)
{
  assert(unit != nullptr);

  auto p(battle->map()->graphicsProperties());

  Image& image(resources::ResourcesManager::getImage(unit->name()));
  // image.sprite()->setColor(Status::player()->unitsColor());

  float x = image.sprite()->getTexture()->getSize().x;
  float y = image.sprite()->getTexture()->getSize().y;
  image.sprite()->setScale(p->cellWidth() / x, p->cellHeight() / y);

# ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (x < p->cellWidth() || y < p->cellHeight()) {
    Debug::logPrintf("Sprite scale failure");
  }
# endif

  // if (unit->targetable())
  // {
  //   // Unit's image halo
  //   Image &highlight = GETIMAGE("highlight");
  //   highlight.sprite()->setColor(sf::Color(255, 0, 0));
  //   highlight.drawAtCell(unit->coords());
  // }

  if (unit->played()) {
    image.sprite()->setColor(sf::Color(127, 127, 127, 191));
  }

  image.drawAtCell(unit->coords(), p);
}


void GraphicsEngine::setWindow(std::unique_ptr<sf::RenderWindow> window) {
  _window = std::move(window);
}


void GraphicsEngine::setGridOffset(const std::shared_ptr<Map> map)
{
  auto p(map->graphicsProperties());

  // offset = 1/2 left room
  p->setGridOffsetX((_window->getSize().x - p->cellWidth() * map->nbColumns()) / 2);
  p->setGridOffsetY((_window->getSize().y - p->cellHeight() * map->nbLines()) / 2);
}



} // namespace graphics
