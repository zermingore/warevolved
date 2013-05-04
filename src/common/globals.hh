#ifndef GLOBALS_HH_
# define GLOBALS_HH_

# include <common/Settings.hh>
# include <common/Status.hh>


// keeping a pointer to the main Setting instance
extern Settings *g_settings;

// keeping all game status (map attributes, menu status, ...)
extern Status *g_status;

#endif /* !GLOBALS_HH_ */
