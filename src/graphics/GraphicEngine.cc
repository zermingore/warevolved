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
  _IDTST = 0;
}

GraphicEngine::~GraphicEngine() {
}

void GraphicEngine::initRoom()
{
  // = scroll ? 0 : (g_status->getCellWidth() + g_status->getCellHeight()) / 4;
  if (1) // !scroll // TODO split offset bottom, ...
  {
    g_status->setGridOffsetX((g_status->getRenderX() - CELL_WIDTH * g_status->getMap()->getNbColumns()) / 2);
    g_status->setGridOffsetY((g_status->getRenderY() - CELL_HEIGHT * g_status->getMap()->getNbLines()) / 2);
  }
}


void GraphicEngine::drawScene()
{
  this->drawBackground();

  this->drawPanel();
  this->drawMenuBar();
  this->initRoom(); // TODO call only @init and when needed (panelPosition modified)

  this->drawCells();
  this->drawGrid();

  this->drawInterface();
}


void GraphicEngine::drawBackground() // TODO (map background)
{
  return;
}

void GraphicEngine::drawPanel()
{
  if (g_interface->getPanelPosition() == E_PANEL_DEACTIVATED)
    return;

  // TODO manage removal
  // TODO update render zone size if there's a new panel

  // for now, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
    sf::Vector2f (0.66f * WINDOW_SIZE_X, 0),
    sf::Vector2f (0.66f * WINDOW_SIZE_X, WINDOW_SIZE_Y)
  };
  WINDOW->draw(line, 2, sf::Lines);
}

void GraphicEngine::drawMenuBar()
{
  if (g_interface->getMenuBarPosition() == E_MENU_BAR_DEACTIVATED)
    return;

  // TODO manage removal
  // TODO update render zone size if there's a new bar

  // for now, drawing a line to delimit the menu zone
  sf::Vertex line[2] = {sf::Vector2f (0, CELL_HEIGHT / 2),
						sf::Vector2f (WINDOW_SIZE_X, (CELL_WIDTH + CELL_HEIGHT) / 4)};
  WINDOW->draw(line, 2, sf::Lines);
}


void GraphicEngine::drawCells()
{
  for (unsigned int i = 0; i < g_status->getMap()->getNbColumns(); ++i)
    for (unsigned int j = 0; j < g_status->getMap()->getNbLines(); ++j)
  	{
      //e_terrains terrain = g_status->getMap()->getTerrain(i, j);
      // _rm->getImage(E_TYPES_TERRAIN, [g_status->getMap()->getTerrain(i, j)])->draw()
      // _rm->getImage(g_status->getMap()->getTerrainId())->draw(i, j);

      GETIMAGE(&_IDTST, std::string("forest"))->drawAtCell(i, j);

      Unit *unit = g_status->getMap()->getUnit(i, j);
      if (unit)
        unit->draw();
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


void GraphicEngine::drawInterface() {
  g_interface->draw();
}
