/*
 * common/globals.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GLOBALS_HH_
# define GLOBALS_HH_

# include <interface/Interface.hh>
# include <common/Settings.hh>
# include <common/Status.hh>


/** \brief keeping a pointer to the main Setting instance */
extern std::unique_ptr<Settings> g_settings;

/** \brief keeping all game status (map attributes, ...) */
extern std::unique_ptr<Status> g_status;

/** \brief keeping all interface settings (menu status, ...) */
extern std::unique_ptr<Interface> g_interface;

/** \brief Resources Manager keeper */
extern std::unique_ptr<ResourcesManager> g_rm;

/** \brief pointer on the main graphic window */
extern std::unique_ptr<sf::RenderWindow> g_window;

#endif /* !GLOBALS_HH_ */
