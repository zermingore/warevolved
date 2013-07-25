#ifndef GLOBALS_HH_
# define GLOBALS_HH_

# include <interface/Interface.hh>
# include <common/Settings.hh>
# include <common/Status.hh>


/** \brief keeping a pointer to the main Setting instance */
extern Settings *g_settings;

/** \brief keeping all game status (map attributes, ...) */
extern Status *g_status;

/** \brief keeping all interface settings (menu status, ...) */
extern Interface *g_interface;

/** \brief ResourceManager keeper */
extern ResourcesManager* g_rm;

#endif /* !GLOBALS_HH_ */
