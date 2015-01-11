#include <interface/panels/PanelElement.hh>
#include <common/globals.hh>


PanelElement::PanelElement(std::string label_name, e_panel entry)
{
  _background = GETIMAGE("selection_menu_button");
  _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));

  // label initialization
  // TODO better calculus, ratio dependent, eventually, text length dependent
  _label = std::make_shared<sf::Text> ();
  _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 8);

  _font = g_rm->getFont("font_army");
  _label->setFont(*(_font.getFont()));
  _label->setString(label_name);

  _id = entry;
}
