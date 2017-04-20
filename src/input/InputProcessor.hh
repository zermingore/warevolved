/**
 * \file
 * \date October 6, 2016
 * \author Zermingore
 */

#ifndef INPUT_INPUT_PROCESSOR_HH_
# define INPUT_INPUT_PROCESSOR_HH_

# include <chrono>
# include <memory>
# include <queue>
# include <input/EventManager.hh>

class KeyManager;


/**
 * \class InputProcessor
 * \brief Processes events through the States EventManagers
 */
class InputProcessor
{
public:
  /// Instanciates a KeyManager
  InputProcessor(bool replay);

  /// Default destructor
  ~InputProcessor() = default;


  /**
   * \brief process events.
   */
  bool process();

  /**
   * \brief process events from a replay
   */
  bool replay();


  /**
   * \brief key manager getter
   */
  auto keyManager() { return _km; }


private:
  /// Event managers queue
  std::deque<std::shared_ptr<EventManager>> _managers;

  /// Key Manager to handle Hardware input
  std::shared_ptr<KeyManager> _km;

  /// Events contained in the replay (with timestamps)
  std::vector<std::pair<std::chrono::duration<double>, int>> _replayEvents;
};


#endif /* INPUT_INPUT_PROCESSOR_HH_ */
