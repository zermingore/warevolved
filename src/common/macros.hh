#ifndef MACROS_HH_
# define MACROS_HH_

# define WINDOW g_status->window()
# define WINDOW_SIZE_X g_status->window()->getSize().x
# define WINDOW_SIZE_Y g_status->window()->getSize().y

# define CELL_WIDTH g_status->cellWidth()
# define CELL_HEIGHT g_status->cellHeight()
# define GRID_THICKNESS g_status->gridThickness()
# define GRID_OFFSET_X g_status->gridOffsetX()
# define GRID_OFFSET_Y g_status->gridOffsetY()
# define NB_COLUMNS g_status->map()->nbColumns()
# define NB_LINES g_status->map()->nbLines()

# define CURSOR g_interface->cursor()
# define CURRENT_MODE g_status->currentMode()

/** \brief SFML key detection
 **   \return true if one of the two possible binding
 **     of a function has been triggered
 **   \return false otherwise
 **   \param feature key name auto expand _1 and _2 to this name
 */
# define PRESSED(x) sf::Keyboard::isKeyPressed(_keys[ x ##_1]) || \
    sf::Keyboard::isKeyPressed(_keys[ x ##_2])
# define GETIMAGE g_rm->getImage


#endif /* !MACROS_HH_ */
