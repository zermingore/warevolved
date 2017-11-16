/**
 * \file
 * \date April 18, 2013
 * \author Zermingore
 * \brief Global game status accessor, including current Player, State, ...
 */

#ifndef COMMON_STATUS_HH_
# define COMMON_STATUS_HH_

# include <mutex>
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



namespace game {

/// \todo Status no longer static and destructor pops every States

/**
 * \class Status
 * \brief stores game status information such as current player, battle, ...
 */
class Status
{
public:
  /// Battle getter
  static auto battle() { return _battle; }

  /// Battle setter
  static void setBattle(const std::shared_ptr<Battle> battle) {
    _battle = battle;
  }

  static void setInputProcessor(const std::shared_ptr<InputProcessor> processor)
  {
    _inputProcessor = processor;
  }


  /**
   * \brief return current state
   * meaning, the top of _states stack
   * does *NOT* pop the stack
   */
  static std::shared_ptr<State> currentState();

  /**
   * \brief returns the current state identifier
   */
  static e_state state();

  /**
   * \brief stacks a new state on _states
   * \param state state we just entered
   */
  static void pushState(const e_state state);

  /**
   * \brief pops _states and blocks the inputs
   */
  static void popCurrentState();

  /**
   * \brief Clears states stack until the playing state
   * \note The stack must not be empty and must contain e_state::PLAYING
   */
  static void clearStates();


  /**
   * \brief Switch to the next Player
   */
  static void nextPlayer();



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
  /// Prevent from getting a State not fully built/destroyed
  static std::mutex _lock;

  /**
   * \brief Ignore every input for a short time period (default: 100ms)
   * \param duration Delay in ms before re-considering input
   * \note Useful when changing State to ignore involuntary but valid input
   */
  static void blockInputs(const size_t duration = 100);


  /// States stack: storing a pointer to the state and its (more specific) type
  static std::stack<std::pair<e_state, std::shared_ptr<State>>> _states;

  /// Global State handling inputs accessible everywhere
  static std::shared_ptr<State> _globalState;

  static std::shared_ptr<Battle> _battle; ///< pointer on Battle
  static Coords _selectedCell; ///< coordinates of the selected cell
  static Coords _selectedUnitPosition; ///< current selected Unit's coordinates
  static std::shared_ptr<InputProcessor> _inputProcessor; ///< input processor
};


} // namespace game


#endif /* !COMMON_STATUS_HH_ */
