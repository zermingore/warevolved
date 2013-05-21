#ifndef GLOBALS_HH_
# define GLOBALS_HH_

# include <interface/Interface.hh>
# include <common/Settings.hh>
# include <common/Status.hh>


// keeping a pointer to the main Setting instance
extern Settings *g_settings;

// keeping all game status (map attributes, ...)
extern Status *g_status;

// keeping all interface settings (menu status, ...)
extern Interface *g_interface;

// ResourceManager keeper
extern ResourcesManager* g_rm;

#endif /* !GLOBALS_HH_ */
