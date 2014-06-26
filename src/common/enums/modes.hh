/*
 * common/enums/modes.hh
 *
 *  Created on: July 24, 2013
 *      Author: Zermingore
 */

#ifndef MODES_HH_
# define MODES_HH_

/** \enum various menu mode values
 ** use this to notify the mode stack
 */
enum e_mode
{
  E_MODE_NONE = 0, // we should never be in this mode

  E_MODE_MAIN_MENU,
  E_MODE_IN_GAME,
  E_MODE_PLAYING,

  E_MODE_SELECTION_MENU, // pick a Unit
  E_MODE_MOVING_UNIT, // move it
  E_MODE_ACTION_MENU, // give it an order
  E_MODE_ATTACK, // ask a Unit to attack

  E_MODE_LOADING,
  E_MODE_SAVING,

  E_MODE_READ_TEXTBOX,
  E_MODE_WRITE_MESSAGE
};


#endif /* !MODES_HH_ */
