#ifndef GLOBALS_HH_
# define GLOBALS_HH_

# include <common/Settings.hh>

// keeping a pointer to the main Setting instance
extern Settings* g_player_settings;

// a cell is a square
extern unsigned int g_cell_size; // in px

// cell delimiter thickness
extern unsigned int g_grid_thickness; // in px

// TODO move in a Settings instance
// required time to consider a "second pressure"
extern int g_key_repeat_delay; // in ms, must be > 0 to avoid locking keyboard

#endif /* !GLOBALS_HH_ */
