/**
 * \file
 * \date April 18, 2013
 * \author Zermingore
 * \brief Global game status accessor, including current Player, State, ...
 */

#ifndef STATUS_HH_
# define STATUS_HH_

# include <memory>
# include <stack>
# include <common/using.hh>


class State;
class Battle;
class Player;
class InputProcessor;

namespace interface {
  class Interface;
}

enum class e_state;


/**
 * \class Status
 * \brief stores game status information such as current player, battle, ...
 */
class Status
{
public:
  /**
   * \brief Destructor. Pops every state
   */
  ~Status();


  // ________________________________ Battle ________________________________ //
  /// Battle getter
  static std::shared_ptr<Battle> battle() { return _battle; }

  /// Battle setter
  static void setBattle(std::shared_ptr<Battle> battle) { _battle = battle; }


  // ________________________________ Events ________________________________ //
  static void setInputProcessor(std::shared_ptr<InputProcessor> processor) {
    _inputProcessor = processor;
  }


  // ________________________________ States ________________________________ //
  /**
   * \brief pops _states summit
   * exits the game if the stack is empty
   * \param skip retrieve Cursor position or not
   */
  static void exitCurrentState();

  /**
   * \brief pops _states and returns summit
   * \return Menu of the top of the stack
   */
  static std::shared_ptr<State> popCurrentState();

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


  // _______________________________ Wrappers _______________________________ //
  /**
   * \brief wrapper to the battle to get the current player
   * \return current player
   */
  static std::shared_ptr<Player> player();

  /**
   * \brief wrapper to the battle to get the current player
   * \return current player
   */
  static std::shared_ptr<interface::Interface> interface();


private:
  static std::stack<std::shared_ptr<State>> _states; ///< States stack
  static std::shared_ptr<Battle> _battle; ///< pointer on Battle
  static Coords _selectedCell; ///< coordinates of the selected cell
  static Coords _selectedUnitPosition; ///< current selected Unit's coordinates
  static std::shared_ptr<InputProcessor> _inputProcessor;
};


#endif /* !STATUS_HH_ */
