/**
 * \file
 * \date July 27, 2017
 * \author Zermingore
 */

#ifndef STATE_GLOBAL_HH_
# define STATE_GLOBAL_HH_

# include <context/State.hh>


/**
 * \class StateGlobal
 * \brief State which is always present.
 *   It tries to treat events not handled by the current State
 */
class StateGlobal: public State
{
public:
  /**
   * \brief Registers to callbacks
   */
  StateGlobal();

  /**
   * \brief Default destructor
   */
  ~StateGlobal() = default;


  /**
   * \brief Explicitly draw nothing.
   */
  void draw() override final {}


  /**
   * \brief Saves the current rendered image into a file
   */
  void screenshot();

  /**
   * \brief Toggles the side panel position
   */
  void togglePanel();
};



#endif /* !STATE_GLOBAL_HH_ */
