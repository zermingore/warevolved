#include <interface/panels/PanelElement.hh>


PanelElement::PanelElement(std::string label_name, e_panel entry)
{
  // _background = GETIMAGE("selection_menu_button");
  // _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));

  _backgroundName = "selection_menu_button";

  // label initialization
   /// \todo better calculus, ratio dependent, eventually, text length dependent
  // _label = std::make_shared<sf::Text> ();
  // _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 8);

  // _font = g_rm->getFont("font_army");
  // _label->setFont(*(_font.getFont()));
  // _label->setString(label_name);

  _id = entry;

  _size = sf::Vector2f(5, 5);
  static sf::Vector2f static_pos = sf::Vector2f(0, 0);
  _position = static_pos;
  static_pos += _size;
}


void PanelElement::draw()
{
  // _background.setPosition(_position);
  // _label->setPosition(_position);

  // _background.draw();
  // g_window->draw(*_label);
}
