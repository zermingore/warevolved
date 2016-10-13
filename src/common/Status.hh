#ifndef STATUS_HH_
# define STATUS_HH_


# include <memory>
# include <stack>
# include <common/using.hh>

class State;
class Battle;
class InGameMenu;

enum class e_state;


/**
 * \brief stores game status information such as
 *   last cell selected, current player, ...
 */
class Status
{
public:
  /**
   * \brief Destructor. Pops every state
   */
  ~Status();

  /**
   * \brief initializes selectedUnitPosition
   */
  void initialize();

  // keeps clicked cell's coordinates in _selectedCell
  // void cellSelection();

  // __________________________ Getters / Setters __________________________ //
  /**
   * \brief returns selected cell's coordinates
   */
  static Coords selectedCell() { return _selectedCell; }

  /**
   * \brief pops _states summit
   * exits the game if the stack is empty
   * \param skip retrieve Cursor position or not
   */
  static void exitCurrentState(const bool skip = false);

  /**
   * \brief pops _states summit while current state <> state
   * exits the game if the stack is empty
   * \param skip retrieve Cursor position or not
   */
  static void exitToState(e_state state, bool skip = false);

  /**
   * \brief pops _states and returns summit
   * \return Menu of the top of the stack
   */
  static std::shared_ptr<State> popCurrentState();

  // /**
  //  * \brief return current state
  //  * meaning, the top of _states stack's state
  //  * does *NOT* pop the stack
  //  */
  // static e_state currentState();

  /**
   * \brief return current state
   * meaning, the top of _states stack
   * does *NOT* pop the stack
   */
  static std::shared_ptr<State> currentState();

  /**
   * \brief stacks a new state on _states
   * \param state state we just entered
   */
  static void pushState(e_state state);

  /**
   * \brief stacks a new state on _states
   * \param state state we just entered
   */
  static void pushStateInGameMenu(e_state state, std::shared_ptr<InGameMenu> menu);

  /**
   * \brief sets selected cell coordinates to the given coordinates
   * \param c coordinates of the selected cell
   */
  static void setSelectedCell(Coords c) { _selectedCell = c; }

  /**
   * \brief _selectedUnitPosition getter
   * \return _selectedUnitPosition
   */
  static Coords selectedUnitPosition() { return _selectedUnitPosition; }

  /**
   * \brief _selectedUnitPosition setter
   * \param pos selected Unit position
   */
  static void setSelectedUnitPosition(Coords pos) {
    _selectedUnitPosition = pos;
  }


private:
  static std::stack<std::shared_ptr<State>> _states; ///< States stack
  static std::shared_ptr<Battle> _battle; ///< pointer on Battle
  static Coords _selectedCell; ///< coordinates of the selected cell
  static Coords _selectedUnitPosition; ///< current selected Unit's coordinates
};


#endif /* !STATUS_HH_ */
