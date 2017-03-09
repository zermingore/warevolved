/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 */

#ifndef CORE_CONTEXT_HH_
# define CORE_CONTEXT_HH_

# include <memory>

class System;

/**
 * \class Context
 * \brief Describes a graphical context
 */
class Context
{
public:
  /// \brief deleted default Constructor
  Context() = delete;

  /**
   * \brief Constructor
   * \param fullscreen true if we're in full screen
   *   false if we're in windowed mode
   */
  explicit Context(const bool fullscreen);

  /**
   * \brief default destructor
   */
  ~Context() = default;


private:
  /**
   * \brief Builds and sets the main window
   */
  void init();

  std::shared_ptr<System> _system; ///< System settings (libraries version, ...)
};


#endif /* !CORE_CONTEXT_HH_ */
