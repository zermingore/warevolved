#ifndef CONTEXT_HH_
# define CONTEXT_HH_

# include <common/include.hh>
# include <common/System.hh>
# include <common/Settings.hh>


class Context
{
public:
  /// Create the main window
  Context();
  Context(bool fullscreen);
  ~Context();

  sf::RenderWindow* init();

private:
  sf::RenderWindow* _window;
  Settings* _settings;
  System* _system;
};

#endif /* !CONTEXT_HH_ */
