/**
 * \file
 * \date July 27, 2017
 * \author Zermingore
 * \brief StateGlobal class declaration
 */

#ifndef STATE_GLOBAL_HH_
# define STATE_GLOBAL_HH_

# include <context/State.hh>


/**
 * \class StateGlobal
 * \brief State which is always present.
 *   It tries to treat events not handled by the current State
 */
class StateGlobal final: public State
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
  void screenshot() const;

  /**
   * \brief Dumps the Map on the standard output
   */
  void dumpMap() const;

  /**
   * \brief Save the current Map on the quick save file
   */
  void quickSave() const;

  /**
   * \brief Load the Map from the latest quick load file
   * \todo implement quickLoad()
   */
  void quickLoad() const;
};



#endif /* !STATE_GLOBAL_HH_ */
