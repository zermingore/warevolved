#include <graphics/GraphicsEngine.hh>
#include <common/globals.hh>
#include <common/constants.hh>


void GraphicsEngine::initRoom()
{
  // = scroll ? 0 : (g_status->cellWidth() + g_status->cellHeight()) / 4;
  //if (!scroll) // TODO split offset bottom, ...

  g_status->setGridOffset();
}


void GraphicsEngine::drawScene()
{
  drawBackground();
  drawCells();
  drawGrid();
  g_interface->draw();
}


void GraphicsEngine::drawBackground()
{
  // TODO draw map background
  g_window->clear();
}


void GraphicsEngine::drawCells()
{
  auto cells = CELLS;

  // draws column by column
  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
  {
    for (unsigned int j = 0; j < NB_LINES; ++j)
      cells[i][j]->draw();
  }
}


void GraphicsEngine::drawGrid()
{
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(GRID_COLOR);
  rectangle.setOutlineThickness(5);

  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
  {
  	for (unsigned int j = 0; j < NB_LINES; ++j)
    {
      rectangle.setPosition(i * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X,
                            j * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y);
      g_window->draw(rectangle);
    }
  }
}
