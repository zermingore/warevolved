#ifndef INPUT_PROCESSOR_HH_
# define INPUT_PROCESSOR_HH_

# include <memory>
# include <queue>

class KeyManager;


class InputProcessor
{
public:
  /**
   * \brief process events.
   */
  void process();



private:
  /// Event managers queue
  std::deque<std::shared_ptr<EventManager>> _managers;

  std::shared_ptr<KeyManager> _km;
};


#endif /* INPUT_PROCESSOR_HH_ */
