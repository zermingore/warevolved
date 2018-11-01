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
  ~StateGlobal() override = default;


  /**
   * \brief Explicitly draw nothing.
   */
  void draw() override final {}


  /**
   * \brief Saves the current rendered image into a file
   */
  void screenshot();

  /**
   * \brief Dumps the Map on the standard output
   */
  void dumpMap();

  /**
   * \brief Save the current Map on the quick save file
   */
  void quickSave();

  /**
   * \brief Load the Map from the latest quick load file
   */
  void quickLoad();
};



#endif /* !STATE_GLOBAL_HH_ */
