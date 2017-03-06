/*
 * core/Context.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef CONTEXT_HH_
# define CONTEXT_HH_

# include <memory>

class System;

class Context
{
public:
  /// \brief deleted default Constructor
  Context() = delete;

  /**
   * \brief Constructor
   * \param fullscreen equals true if we're in full screen
   *   false if we're in windowed mode
   */
  explicit Context(bool fullscreen);


  /**
   * \brief default destructor
   */
  ~Context() = default;


private:
  /**
   * \brief Builds and sets the main window
   */
  void init();

  std::shared_ptr<System> _system; ///< System settings (SFML version, ...)
};

#endif /* !CONTEXT_HH_ */
