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
   * \brief Instanciates a KeyManager
   * \param replay \true to set the InputsListener in replay mode,
   *   reading events from a file instead of the keyboard
   * \see KeyManager
   */
  InputsListener(bool replay);

  /**
   * \brief Default destructor
   */
  ~InputsListener() = default;


  /**
   * \brief KeyManager getter
   * \return A pointer on the KeyManager
   */
  auto keyManager() { return _km; }


  /**
   * \brief Polls events until the exit event was found
   * \note infinit loop polling events, populating the KeyManager events queue
   */
  void pollEvents();


private:
  /// Key Manager to handle Hardware input
  std::shared_ptr<KeyManager> _km;

  /// Events contained in the replay (with timestamps)
  std::vector<std::pair<std::chrono::duration<double>, int>> _replayEvents;

  bool _replay; ///< Use input from a replay file

  /// Creation of the InputsListener timestamp
  std::chrono::steady_clock::time_point _creationTime;
};


#endif /* !INPUT_INPUTS_LISTENER_HH_ */
