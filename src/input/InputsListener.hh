/**
 * \file
 * \date June 21, 2017
 * \author Zermingore
 * \brief InputsListener declaration
 */

#ifndef INPUT_INPUTS_LISTENER_HH_
# define INPUT_INPUTS_LISTENER_HH_

# include <string>
# include <utility> // std::pair
# include <vector>
# include <chrono>


/**
 * \class InputsListener
 * \brief Listen to keyboard events and register them into an events fifo
 */
class InputsListener
{
public:
  /**
   * \brief Polls events until the exit event was found
   * \param replay \true if we're in replay mode
   * \note Infinite loop polling events, populating the KeyManager events queue
   * \note Initialize the KeyManager
   * \note In replay mode, launches another thread reading inputs from the replay
   */
  static void listen(bool replay);


private:
  /**
   * \brief Extract e_keys and associated timestamps used during a previous run.
   * \param filename Replay file name to use
   * \note the format of the given file is expected to be: timestamp<space>e_key
   * \note every lines not respecting this syntax will be skipped
   */
  static void getReplayKeys(const std::string& filename);

  /**
   * \brief Push the replay events in the KeyManager events queue
   *  at their recorded time
   */
  static void replay();


  using EventsList = std::vector<std::pair<std::chrono::duration<double>, int>>;

  /// List of events recorded during a previous game
  static EventsList _replayEvents;
};


#endif /* !INPUT_INPUTS_LISTENER_HH_ */
