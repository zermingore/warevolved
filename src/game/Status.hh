/**
 * \file
 * \brief Global game status accessor, including current Player, State, ...
 * \author Zermingore
 * \date April 18, 2013
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

namespace interface {
  class Interface;
}

enum class e_state;
enum class e_input;



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


  /**
   * \brief Resume the current state (at the top of _states stack)
   * \note does *NOT* pop the stack
   */
  static void resumeState();

  /**
   * \brief Resume the current state (at the top of _states stack)
   * \note does *NOT* pop the stack
   */
  template<typename... Attributes>
  static void setStateAttributes(Attributes... attributes);

  /**
   * \brief Draw the current State
   */
  static void drawState();

  /**
   * \brief Process the given input
   * \param input Input from the KeyManager to process
   * \return \true if a callback was found; \false otherwise
   */
  static bool processInput(const e_input& input);

  /**
   * \brief returns the current state
   * \return Current state (top of the stack) identifier
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
  /**
   * \brief Ignore every input for a short time period (default: 100ms)
   * \param duration Delay in ms before re-considering input
   * \note Useful when changing State to ignore involuntary but valid input
   */
  static void blockInputs(const size_t duration = 100);


  /// Prevent from getting a State not fully built/destroyed
  static std::mutex _lock;

  /// States stack: storing a pointer to the state and its (more specific) type
  static std::stack<std::pair<e_state, std::unique_ptr<State>>> _states;

  /// Global State handling inputs accessible everywhere
  static std::shared_ptr<State> _globalState;

  static std::shared_ptr<Battle> _battle; ///< pointer on Battle
  static Coords _selectedCell; ///< coordinates of the selected cell
  static Coords _selectedUnitPosition; ///< current selected Unit's coordinates
};


} // namespace game


# include <game/Status.hxx>

#endif /* !COMMON_STATUS_HH_ */
