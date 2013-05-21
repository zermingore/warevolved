#include <common/include.hh>
#include <graphics/GraphicEngine.hh>
#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/units.hh>
#include <common/terrains.hh>
#include <game/Map.hh>
#include <common/types.hh>


GraphicEngine::GraphicEngine()
{
  g_status->getMap()->init(); // TODO move
  _cursor = new Cursor(8, 8);
  g_status->setCursor(_cursor);
  _selectionMenu = g_interface->getSelectionMenu();

  _IDTST = 0;
}

GraphicEngine::~GraphicEngine() {
  delete _cursor;
}


void GraphicEngine::drawScene()
{
  this->drawBackground();

  this->drawPanel();
  this->drawMenuBar();

  this->drawCells();
  this->drawGrid();
  this->drawCursor();

  this->drawSelectionMenu();
}

void GraphicEngine::drawBackground() // TODO (map background)
{
  return;
}

void GraphicEngine::drawPanel()
{
  if (g_status->getPanelPosition() == E_PANEL_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new panel

  // for now, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
	sf::Vector2f (0.66f * g_status->getWindow()->getSize().x, 0),
	sf::Vector2f (0.66f * g_status->getWindow()->getSize().x, g_status->getWindow()->getSize().y)
  };
  g_status->getWindow()->draw(line, 2, sf::Lines);
}

void GraphicEngine::drawMenuBar()
{
  if (g_status->getMenuBarPosition() == E_MENU_BAR_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new bar

  // for now, drawing a line to delimit the menu zone
  sf::Vertex line[2] = {sf::Vector2f (0, CELL_HEIGHT / 2),
						sf::Vector2f (g_status->getWindow()->getSize().x, (CELL_WIDTH + CELL_HEIGHT) / 4)};
  g_status->getWindow()->draw(line, 2, sf::Lines);
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
  sf::Color grid_color(202, 124, 0);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_status->getCellWidth(), g_status->getCellHeight()));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  // = scroll ? 0 : (g_status->getCellWidth() + g_status->getCellHeight()) / 4;
  g_status->setGridOffsetX(0);
  g_status->setGridOffsetY(0);
  if (1) // !scroll // TODO split offset bottom, ...
  {
	g_status->setGridOffsetX((g_status->getRenderX() - g_status->getCellWidth() * g_status->getMap()->getNbColumns()) / 2);
	g_status->setGridOffsetY((g_status->getRenderY() - g_status->getCellHeight() * g_status->getMap()->getNbLines()) / 2);
  }

  for (unsigned int i = 0; i < g_status->getMap()->getNbColumns(); ++i)
  	for (unsigned int j = 0; j < g_status->getMap()->getNbLines(); ++j)
	{
	  rectangle.setPosition(i * g_status->getCellWidth() + g_status->getGridThickness() + g_status->getGridOffsetX(),
							j * g_status->getCellHeight() + g_status->getGridThickness() + g_status->getGridOffsetY());
	  g_status->getWindow()->draw(rectangle);
	}
}


void GraphicEngine::drawCursor()
{
  // if (_cursor->getVisible())
  _cursor->getSprite(g_status->getGridOffsetX(), g_status->getGridOffsetY());
  _cursor->draw();
}


void GraphicEngine::drawSelectionMenu()
{
  // draw this menu only if requested
  if (!g_status->getSelectionMode())
	return;

  _selectionMenu->draw();
}
