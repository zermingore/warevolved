/**
 * \file
 * \date August 24, 2017
 * \author Zermingore
 */

#ifndef ENUM_PANEL_STATUS_HH_
# define ENUM_PANEL_STATUS_HH_


/**
 * \enum e_panel_status
 * \brief List the possible locations of the interface side panel
 */
enum class e_panel_status
{
  DEACTIVATED = 0,
  POSITION_LEFT,
  POSITION_RIGHT,

  NB_PANEL_STATUS
};


#endif /* !ENUM_PANEL_STATUS_HH_ */
