#ifndef CONTEXT_HH_
# define CONTEXT_HH_

# include <common/include.hh>
# include <common/System.hh>
# include <common/Settings.hh>
# include <common/globals.hh>

class Context
{
public:
  /** \brief default Constructor;
   */
  Context();
  explicit Context(bool fullscreen);
  ~Context();

  /** \brief Builds and returns the main window
   ** \return Main rendering window
   */
  sf::RenderWindow* init();

private:
  sf::RenderWindow* _window; ///< main rendering window
  Settings* _settings; ///< user's settings (full-screen, anti-aliasing, ...)
  System* _system; ///< System settings (SFML version, ...)
};

#endif /* !CONTEXT_HH_ */
