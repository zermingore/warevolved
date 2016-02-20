#ifndef STATUS_HH_
# define STATUS_HH_

# include <memory>
# include <stack>
# include <common/using.hh>
# include <common/enums/modes.hh>

class State;
class Battle;
class InGameMenu;

/** \brief stores game status information such as
 **   last cell selected, current player, ...
 */
class Status
{
public:
  /** \brief Destructor
   *
   * Pops every state
   */
  ~Status();

  /** \brief initializes selectedUnitPosition
   */
  void initialize();

  // /** \brief keeps clicked cell's coordinates in _selectedCell
  //  */
  // void cellSelection();

  // __________________________ Getters / Setters __________________________ //
  /** \brief returns selected cell's coordinates
   */
  static Coords selectedCell() { return _selectedCell; }

  /** \brief pops _modes summit
   ** exits the game if the stack is empty
   ** \param skip retrieve Cursor position or not
   */
  static void exitCurrentMode(const bool skip = false);

  /** \brief pops _modes summit while current mode <> mode
   ** exits the game if the stack is empty
   ** \param skip retrieve Cursor position or not
   */
  static void exitToMode(e_mode mode, bool skip = false);

  /** \brief pops _modes and returns summit
   ** \return Menu of the top of the stack
   */
  static std::shared_ptr<State> popCurrentMode();

  /** \brief return current mode
   ** meaning, the top of _modes stack's mode
   ** does *NOT* pop the stack
   */
  static e_mode currentMode();

  /** \brief return current state
   ** meaning, the top of _modes stack
   ** does *NOT* pop the stack
   */
  static std::shared_ptr<State> currentState();

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  static void pushMode(e_mode mode);

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  static void pushModeInGameMenu(e_mode mode, std::shared_ptr<InGameMenu> menu);

  /** \brief sets selected cell coordinates to the given coordinates
   ** \param c coordinates of the selected cell
   */
  static void setSelectedCell(Coords c) { _selectedCell = c; }

  /** \brief _selectedUnitPosition getter
   ** \return _selectedUnitPosition
   */
  static Coords selectedUnitPosition() { return _selectedUnitPosition; }

  /** \brief _selectedUnitPosition setter
   ** \param pos selected Unit position
   */
  static void setSelectedUnitPosition(Coords pos) { _selectedUnitPosition = pos; }


private:
  static std::stack<std::shared_ptr<State>> _states; ///< States stack
  static std::shared_ptr<Battle> _battle; ///< pointer on Battle
  static Coords _selectedCell; ///< coordinates of the selected cell
  static Coords _selectedUnitPosition; ///< current selected Unit's coordinates
};


#endif /* !STATUS_HH_ */
