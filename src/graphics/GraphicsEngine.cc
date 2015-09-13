#include <common/constants.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/Unit.hh>


namespace graphics {

const std::string DEFAULT_RESOURCES_XML_FILE = "resources.xml";

// Static Variables definition
std::unique_ptr<sf::RenderWindow> GraphicsEngine::_window;
float GraphicsEngine::_currentFPS;
size_t GraphicsEngine::_renderX;
size_t GraphicsEngine::_renderY;


void initialize()
{
  resources::ResourcesManager::initialize(DEFAULT_RESOURCES_XML_FILE);
  // MapGraphicsProperties::initialize();
}


// void GraphicsEngine::initRoom()
// {
//   // = scroll ? 0 : (cellWidth() + cellHeight()) / 4;
//   //if (!scroll) // TODO split offset bottom, ...

//   setGridOffset(map);
// }


void GraphicsEngine::drawScene(const std::shared_ptr<Map> map)
{
  drawBackground();
  drawMap(map);
  drawGrid(map);

  // draw interface of current_player

  // update the window
  _window->display();
}


void GraphicsEngine::drawBackground()
{
  // TODO draw map background
  _window->clear();
}


void GraphicsEngine::drawMap(const std::shared_ptr<Map> map)
{
  // re-checking grid offsets
  setGridOffset(map);

  // drawing cells (their background and their content)
  std::vector<std::vector<std::shared_ptr<Cell>>> cells = map->cells();

  // TODO [Optimization] fetch every terrains first

  // draws column by column
  for (auto i = 0u; i < map->nbColumns(); ++i)
  {
    for (auto j = 0u; j < map->nbLines(); ++j)
    {
      // TODO check if we print the cell (scroll case)

      const std::shared_ptr<Cell> c = cells[i][j];
      switch (c->terrain())
      {
        default:
          auto img = resources::ResourcesManager::getImage("forest");
          img.drawAtCell(c->coords(), map->graphicsProperties());
          break;
      }

      if (c->highlight())
      {
        Image& highlight = resources::ResourcesManager::getImage("highlight");
        highlight.sprite()->setColor(c->highlightColor());
        highlight.drawAtCell(c->coords(), map->graphicsProperties());
      }

      if (c->unit())
        drawUnit(c->unit());
    }
  }
}


void GraphicsEngine::drawGrid(const std::shared_ptr<Map> map)
{
  auto p(map->graphicsProperties());
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(p->cellWidth(), p->cellHeight()));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(GRID_COLOR);
  rectangle.setOutlineThickness(5);

  // auto p = std::make_shared<Map::MapGraphicsProperties> (map->graphicsProperties());
  auto offset_x = p->cellWidth()  + p->gridThickness() + p->gridOffsetX();
  auto offset_y = p->cellHeight() + p->gridThickness() + p->gridOffsetY();
  for (auto i = 0u; i < map->nbColumns(); ++i)
  {
   for (auto j = 0u; j < map->nbLines(); ++j)
    {
      rectangle.setPosition(i * offset_x, j * offset_y);
      _window->draw(rectangle);
    }
  }
}


void GraphicsEngine::drawUnit(const std::shared_ptr<Unit> unit)
{
  if (!unit)
    return;
}


void GraphicsEngine::setWindow(std::unique_ptr<sf::RenderWindow> window)
{
  _window = std::move(window);

  // initialize render room
  _renderX = _window->getSize().x;
  _renderY = _window->getSize().y;
}

void GraphicsEngine::setGridOffset(const std::shared_ptr<Map> map)
{
  auto p(map->graphicsProperties());

  // offset = 1/2 left room
  p->setGridOffsetX((_window->getSize().x - p->cellWidth()  * map->nbColumns()) / 2);
  p->setGridOffsetY((_window->getSize().y - p->cellHeight() * map->nbLines()) / 2);
}


template <class T>
void GraphicsEngine::draw(std::shared_ptr<T> drawable, Coords pos, Coords size)
{
  std::cout << "image: " << drawable->imageName() << std::endl;
  drawable->imageName();
}


template <class T>
void GraphicsEngine::draw(std::shared_ptr<T> drawable, Cell c)
{
  std::cout << "image: " << drawable->imageName() << std::endl;
  drawable->imageName();
}

} // namespace graphics
