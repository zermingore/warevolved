/**
 * \file
 * \date June 22, 2017
 * \author Zermingore
 * \brief EventsProcessor declaration
 */


#ifndef INPUT_EVENTS_PROCESSOR_HH_
# define INPUT_EVENTS_PROCESSOR_HH_

# include <memory>
# include <SFML/Window/Event.hpp>
# include <stdnoreturn.h>


class KeyManager;


/**
 * \class EventsProcessor
 * \brief Processes events through the States EventManagers
 * \note Is a thread
 */
class EventsProcessor
{
public:
  /**
   * \brief Process events from the events queue
   * \note does not return
   */
  static void process();
};



#endif /* !INPUT_EVENTS_PROCESSOR_HH_ */