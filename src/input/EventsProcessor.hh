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
   * \brief Initializes the KeyManager
   * \param km KeyManager initialized by the InputListener
   * \see KeyManager
   * \see InputListener
   */
  explicit EventsProcessor(std::shared_ptr<KeyManager> km);

  /**
   * \brief Deleted default constructor
   */
  EventsProcessor() = delete;

  /**
   * \brief Default destructor
   */
  ~EventsProcessor() = default;


  /**
   * \brief Process events from the events queue
   */
  void process();


private:
  /// Key Manager to handle Hardware input
  std::shared_ptr<KeyManager> _km;
};



#endif /* !INPUT_EVENTS_PROCESSOR_HH_ */
