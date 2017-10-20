/**
 * \file
 * \date June 22, 2017
 * \author Zermingore
 * \brief EventsProcessor declaration
 */


#ifndef INPUT_EVENTS_PROCESSOR_HH_
# define INPUT_EVENTS_PROCESSOR_HH_

# include <condition_variable>
# include <memory>
# include <SFML/Window/Event.hpp>
# include <stdnoreturn.h>


class KeyManager;


/**
 * \class EventsProcessor
 * \brief Processes events through the States EventManagers
 * \note Is a thread (and a static class)
 */
class EventsProcessor
{
public:
  /**
   * \brief Process events from the events queue
   * \note does not return
   */
  static void process();

  /**
   * \brief Notify the next frame by the GraphicsEngine
   *   in order to unlock the events processing
   */
  static void notifyFrame();


private:
  static std::mutex _lock;                      ///< Lock between frames
  static std::condition_variable _cv_new_frame; ///< New frame notification
};



#endif /* !INPUT_EVENTS_PROCESSOR_HH_ */
