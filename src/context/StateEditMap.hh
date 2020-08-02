/**
 * \file
 * \date April 5, 2020
 * \author Zermingore
 * \brief StateEditMap class declaration
 */

#ifndef STATE_EDIT_MAP_HH_
# define STATE_EDIT_MAP_HH_

# include <context/State.hh>


/**
 * \class StateEditMap
 * \brief Map editor State
 * \note State derived class
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
   * \brief Draw the editor interface
   */
  virtual void draw() override final;


  /**
   * \brief Edit the cell under the cursor
   */
  void menuCell();
};


#endif /* !STATE_EDIT_MAP_HH_ */
