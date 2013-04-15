#ifndef COMMON_HH_
# define COMMON_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class System
{
public:
  System();
  System(unsigned int sfml_major, unsigned int sfml_minor);
  ~System();

  void setSfmlMajor(unsigned int sfml_major);
  void setSfmlMinor(unsigned int sfml_minor);

  unsigned int getSfmlMajor();
  unsigned int getSfmlMinor();

private:
  /// SFML version
  unsigned int _sfmlMajor;
  unsigned int _sfmlMinor;
};

#endif /* !COMMON_HH_ */
