/*
 * core/Context.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

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

  /** \brief Constructor
   ** \param fullscreen equals true if we're in full screen
   **   false if we're in windowed mode
   */
  explicit Context(bool fullscreen);

  /** \brief Builds and sets the main window
   ** \return Main rendering window
   */
  void init();

private:
  std::shared_ptr<System> _system; ///< System settings (SFML version, ...)
};

#endif /* !CONTEXT_HH_ */
