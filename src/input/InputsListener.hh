/**
 * \file
 * \date June 21, 2017
 * \author Zermingore
 * \brief InputsListener class declaration
 */

#ifndef INPUT_INPUTS_LISTENER_HH_
# define INPUT_INPUTS_LISTENER_HH_

# include <memory>
# include <vector>
# include <chrono>
# include <atomic>

class ReplayManager;


/**
 * \class InputsListener
 * \brief Listen to keyboard events and register them into an events fifo
 */
class InputsListener
{
public:
  /**
   * \brief Polls events until the exit event was found
   * \param replay true if we're in replay mode
   * \param replay_filename Replay file (w/o relative or absolute path)
   * \param replay_header Replay file header optional metadata
   * \param stop_events_listener stop thread condition
   * \note Infinite loop polling events, populating the KeyManager events queue
   * \note Initialize the KeyManager
   * \note In replay mode, launch another thread reading inputs from the replay
   */
  static void listen(bool replay,
                     const std::string& replay_filename,
                     const std::string& replay_header,
                     const std::atomic_bool& stop_events_listener);


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
   * \param replay_mgr Pointer on the replay manager
   */
  static void replay(const std::shared_ptr<ReplayManager>& replay_mgr);
};


#endif /* !INPUT_INPUTS_LISTENER_HH_ */
