/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \namespace graphics
 * \brief Context class declaration
 */

#ifndef CORE_CONTEXT_HH_
# define CORE_CONTEXT_HH_


namespace graphics {



/**
 * \class Context
 * \brief Describes a graphical context
 */
class Context
{
public:
  /**
   * \brief Deleted default constructor
   */
  Context() = delete;

  /**
   * \brief Constructor
   * \param fullscreen true if we're in full screen
   *   false if we're in windowed mode
   */
  explicit Context(const bool fullscreen);

  /**
   * \brief Default destructor
   */
  ~Context() = default;


private:
  /**
   * \brief Builds and sets the main window
   */
  void init();
};



} // namespace graphics

#endif /* !CORE_CONTEXT_HH_ */
