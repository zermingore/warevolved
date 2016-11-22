#ifndef INPUT_PROCESSOR_HH_
# define INPUT_PROCESSOR_HH_

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
  InputProcessor();

  /**
   * \brief process events.
   */
  bool process();

  /**
   * \brief key manager getter
   */
  auto keyManager() { return _km; }


private:
  /// Event managers queue
  std::deque<std::shared_ptr<EventManager>> _managers;

  /// Key Manager to handle Hardware input
  std::shared_ptr<KeyManager> _km;
};


#endif /* INPUT_PROCESSOR_HH_ */
