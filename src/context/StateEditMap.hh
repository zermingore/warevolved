/**
 * \file
 * \date April 5, 2020
 * \author Zermingore
 */

#ifndef STATE_EDIT_MAP_HH_
# define STATE_EDIT_MAP_HH_

# include <context/State.hh>


/**
 * \class StateEditMap
 * \brief Map editor State
 */
class StateEditMap: public State
{
public:
  /**
   * \brief registers to callbacks
   */
  StateEditMap();

  /**
   * \brief Default destructor
   */
  ~StateEditMap() override = default;


  /**
   * \brief Draw the player interface
   */
  virtual void draw() override final;
};


#endif /* !STATE_EDIT_MAP_HH_ */
