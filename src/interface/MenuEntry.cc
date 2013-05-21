#include <interface/MenuEntry.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/macros.hh>


MenuEntry::MenuEntry() {
}

MenuEntry::~MenuEntry() {
}

MenuEntry::MenuEntry(std::string label_name)
{
  _background = GETIMAGE("selection_menu_button");
  _background->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));

  // label initialization
  // TODO better calculus, ratio dependent, eventually, text length dependent
  _label = new sf::Text();
  _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 4);

  _font = g_rm->getFont("font_army");
  _label->setFont(*(_font->getFont()));
  _label->setString(label_name);
}

void MenuEntry::draw(sf::Vector2f position)
{
  _background->setPosition(position);
  _label->setPosition(position);

  _background->draw();
  g_status->getWindow()->draw(*_label);
}
