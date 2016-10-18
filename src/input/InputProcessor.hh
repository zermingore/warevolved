#ifndef INPUT_PROCESSOR_HH_
# define INPUT_PROCESSOR_HH_

# include <memory>
# include <queue>
# include <input/EventManager.hh>


class KeyManager;


class InputProcessor
{
public:
  InputProcessor();

  /**
   * \brief process events.
   */
  bool process();



private:
  /// Event managers queue
  std::deque<std::shared_ptr<EventManager>> _managers;

  /// Key Manager
  std::shared_ptr<KeyManager> _km;
};


#endif /* INPUT_PROCESSOR_HH_ */
