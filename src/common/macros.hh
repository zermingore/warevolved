#ifndef MACROS_HH_
# define MACROS_HH_

# define CELL_WIDTH g_status->getCellWidth()
# define CELL_HEIGHT g_status->getCellHeight()
# define GRID_THICKNESS g_status->getGridThickness()
# define GRID_OFFSET_X g_status->getGridOffsetX()
# define GRID_OFFSET_Y g_status->getGridOffsetY()
# define WINDOW g_status->getWindow()
# define WINDOW_SIZE_X g_status->getWindow()->getSize().x
# define WINDOW_SIZE_Y g_status->getWindow()->getSize().y

# define CURSOR g_status->getCursor()
# define CURRENT_MODE g_status->getCurrentMode()

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
