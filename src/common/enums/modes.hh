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
enum class mode
{
  NONE = 0, // we should never be in this mode

  MAIN_MENU,
  IN_GAME,
  PLAYING,

  SELECTION_MENU, // pick a Unit
  MOVING_UNIT, // move it
  ACTION_MENU, // give it an order
  ATTACK, // ask a Unit to attack

  LOADING,
  SAVING,

  READ_TEXTBOX,
  WRITE_MESSAGE
};


#endif /* !MODES_HH_ */
