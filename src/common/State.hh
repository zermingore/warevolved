/*
 * common/State.hh
 *
 *  Created on: July 24, 2013
 *      Author: Zermingore
 */

#ifndef STATE_HH_
# define STATE_HH_

# include <memory>
# include <common/enums/modes.hh>
# include <common/structures/Vector.hh>

class Menu;

/** \brief state class
 ** stores a state, which is composed of
 **   a cursor position
 **   a mode: \enum state index
 */
class State
{
public:
  /** Constructor
   ** \param mode State mode value
   ** auto fetch Cursor coordinates
   */
  explicit State(mode &mode);

  /** Constructor
   ** \param mode State mode value
   ** auto fetch Cursor coordinates
   */
  State(mode mode, std::shared_ptr<Menu> menu);

  /** _mode getter
   ** \return _mode value
   */
  mode currentMode() { return _currentMode; }

  /** _menu getter
   ** \return _menu a pointer over current menu
   */
  inline std::shared_ptr<Menu> menu() { return _menu; }

  /** _cursorCoords getters
   ** \return _cursorCoords value
   */
  inline Coords cursorCoords() { return _cursorCoords; }


private:
  mode _currentMode; ///< State's mode
  std::shared_ptr<Menu> _menu; ///< menu state to save
  Coords _cursorCoords; ///< Cursor coordinates
                        ///< when the mode was activated
};

#endif /* !STATE_HH_ */
