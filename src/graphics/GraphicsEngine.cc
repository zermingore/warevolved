#include <common/constants.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>
#include <game/Cell.hh>
#include <graphics/MapGraphicsProperties.hh>


namespace graphics {

// Static Variables definition
std::unique_ptr<sf::RenderWindow> GraphicsEngine::_window;
float GraphicsEngine::_currentFPS;
unsigned int GraphicsEngine::_cellWidth; // TODO dynamic, somewhere else (Map ?)
unsigned int GraphicsEngine::_cellHeight; // TODO dynamic, somewhere else (Map ?)
unsigned int GraphicsEngine::_gridThickness;
unsigned int GraphicsEngine::_renderX;
unsigned int GraphicsEngine::_renderY;
unsigned int GraphicsEngine::_gridOffsetX;
unsigned int GraphicsEngine::_gridOffsetY;


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
  for (size_t i = 0; i < map->nbColumns(); ++i)
  {
    for (size_t j = 0; j < map->nbLines(); ++j)
    {
      // TODO check if we print the cell (scroll case)

      const std::shared_ptr<Cell> c = cells[i][j];
      switch (c->terrain())
      {
        default:
          resources::ResourcesManager::getImage("forest").drawAtCell(c->coords(), map->graphicsProperties());
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
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(_cellWidth, _cellHeight));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(GRID_COLOR);
  rectangle.setOutlineThickness(5);

  std::shared_ptr<MapGraphicsProperties> p = map->graphicsProperties();
  unsigned int offset_x = p->cellWidth()  + p->gridThickness() + p->gridOffsetX();
  unsigned int offset_y = p->cellHeight() + p->gridThickness() + p->gridOffsetY();
  for (unsigned int i = 0; i < map->nbColumns(); ++i)
  {
   for (unsigned int j = 0; j < map->nbLines(); ++j)
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
  // offset = 1/2 left room
  _gridOffsetX = (_window->getSize().x - _cellWidth * map->nbColumns()) / 2;
  _gridOffsetY = (_window->getSize().y - _cellHeight * map->nbLines()) / 2;
}


} // namespace graphics
