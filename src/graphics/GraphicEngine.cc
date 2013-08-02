#include <common/include.hh>
#include <graphics/GraphicEngine.hh>
#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/enums/units.hh>
#include <common/enums/terrains.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <common/enums/types.hh>


GraphicEngine::GraphicEngine()
{
  g_status->getMap()->init(); // TODO move
  g_status->resetRender();

  this->initRoom(); // TODO call only @init and when needed (panelPosition modified)
}

GraphicEngine::~GraphicEngine() {
}


void GraphicEngine::initRoom()
{
  // = scroll ? 0 : (g_status->getCellWidth() + g_status->getCellHeight()) / 4;
  //if (!scroll) // TODO split offset bottom, ...
  {
    g_status->setGridOffset();

//    g_status->setGridOffsetX((g_status->getRenderX() - CELL_WIDTH * NB_COLUMNS) / 2);
//    g_status->setGridOffsetY((g_status->getRenderY() - CELL_HEIGHT * NB_LINES) / 2);
  }
}


void GraphicEngine::drawScene()
{
  this->drawBackground();
  this->drawCells();
  this->drawGrid();
  g_interface->draw();
}


void GraphicEngine::drawBackground() // TODO (map background)
{
  WINDOW->clear();
  return;
}


void GraphicEngine::drawCells()
{
  Cell **cells = g_status->getMap()->getCells();
  // draws column by column
  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
    for (unsigned int j = 0; j < NB_LINES; ++j)
  	{
      cells[i * NB_COLUMNS + j]->draw();
  	}
}


void GraphicEngine::drawGrid()
{
  sf::Color grid_color(202, 124, 0); // FIXME Hard-Coded

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  for (unsigned int i = 0; i < g_status->getMap()->getNbColumns(); ++i)
  	for (unsigned int j = 0; j < g_status->getMap()->getNbLines(); ++j)
    {
      rectangle.setPosition(i * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X,
                            j * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y);
      WINDOW->draw(rectangle);
    }
}
