/*
 * mode.hh
 *
 *  Created on: Jul 24, 2013
 *      Author: Zermingore
 */

#ifndef MODE_HH_
# define MODE_HH_

/** \brief various menu mode values
 ** use this to notify the mode stack
 */
enum e_mode
{
  E_MODE_NONE = 0, // we should never be in this mode

  E_MODE_MAIN_MENU,
  E_MODE_IN_GAME,
  E_MODE_PLAYING,

  E_MODE_SELECTION_MENU, // 4
  E_MODE_MOVING_UNIT,
  E_MODE_ACTION_MENU,

  E_MODE_LOADING,
  E_MODE_SAVING,

  E_MODE_READ_TEXTBOX,
  E_MODE_WRITE_MESSAGE,
};


#endif /* MODE_HH_ */
