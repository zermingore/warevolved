#include <common/System.hh>


System::System(unsigned int sfml_major, unsigned int sfml_minor)
{
  _sfmlMajor = sfml_major;
  _sfmlMinor = sfml_minor;
}

System::~System() {
}


void System::setSfmlMajor(unsigned int sfml_major) {
  _sfmlMajor = sfml_major;
}

void System::setSfmlMinor(unsigned int sfml_minor) {
  _sfmlMinor = sfml_minor;
}

unsigned int System::sfmlMajor() {
  return _sfmlMajor;
}

unsigned int System::sfmlMinor() {
  return _sfmlMinor;
}
