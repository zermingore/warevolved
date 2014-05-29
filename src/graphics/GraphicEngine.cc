#include <common/include.hh>
#include <graphics/GraphicEngine.hh>
#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/enums/terrains.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>



void GraphicEngine::initRoom()
{
  // = scroll ? 0 : (g_status->cellWidth() + g_status->cellHeight()) / 4;
  //if (!scroll) // TODO split offset bottom, ...
  {
    g_status->setGridOffset();
  }
}


void GraphicEngine::drawScene()
{
  drawBackground();
  drawCells();
  drawGrid();
  g_interface->draw();
}


void GraphicEngine::drawBackground() // TODO (map background)
{
  WINDOW->clear();
}


void GraphicEngine::drawCells()
{
  std::vector<std::vector<Cell>> cells = g_status->map()->cells();
  // draws column by column
  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
    for (unsigned int j = 0; j < NB_LINES; ++j)
  	{
      cells[i][j].draw();
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

  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
  	for (unsigned int j = 0; j < NB_LINES; ++j)
    {
      rectangle.setPosition(i * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X,
                            j * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y);
      WINDOW->draw(rectangle);
    }
}
