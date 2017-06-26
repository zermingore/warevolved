/**
 * \file
 * \date June 21, 2017
 * \author Zermingore
 * \brief InputsListener declaration
 */

#ifndef INPUT_INPUTS_LISTENER_HH_
# define INPUT_INPUTS_LISTENER_HH_

# include <vector>
# include <chrono>
# include <memory>

# include <SFML/Window/Event.hpp>


class KeyManager;



/**
 * \class InputsListener
 * \brief Listen to keyboard events and register them into an events fifo
 */
class InputsListener
{
public:
  /**
   * \brief Polls events until the exit event was found
   * \note Infinite loop polling events, populating the KeyManager events queue
   * \note Instantiate a KeyManager
   */
  static void listen();

  /**
   * \brief KeyManager getter
   * \return A pointer on the KeyManager
   */
  static auto keyManager() { return _km; }



private:
  /// Key Manager to handle Hardware input
  static std::shared_ptr<KeyManager> _km;

  /// Events contained in the replay (with timestamps)
  // std::vector<std::pair<std::chrono::duration<double>, int>> _replayEvents;

  // bool _replay; ///< Use input from a replay file

  // /// Creation of the InputsListener timestamp
  // std::chrono::steady_clock::time_point _creationTime;
};


#endif /* !INPUT_INPUTS_LISTENER_HH_ */
