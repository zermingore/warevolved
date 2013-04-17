#ifndef GLOBALS_HH_
# define GLOBALS_HH_

// a cell is a square
extern unsigned int g_cell_size; // in px

// cell delimiter thickness
extern unsigned int g_grid_thickness; // in px


// game board size
extern unsigned int g_gridSizeX;
extern unsigned int g_gridSizeY;

extern int g_key_repeat_delay; // in milliseconds, must be > 0 to avoid locking keyboard; timers are signed int though


#endif /* !GLOBALS_HH_ */
