#include <interface/InterfaceElement.hh>
#include <common/globals.hh>


void InterfaceElement::draw()
{
  _background.setPosition(_position);
  _label->setPosition(_position);

  _background.draw();
  g_window->draw(*_label);
}
