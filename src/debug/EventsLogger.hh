/**
 * \file
 * \date March 20, 2017
 * \author Zermingore
 */

#ifndef EVENTS_LOGGER_HH_
# define EVENTS_LOGGER_HH_

# include <string>
# include <chrono>
# include <SFML/Window.hpp>

enum class e_input;


/// \todo EventLogger no longer in debug namespace (as it's used for replays)
namespace debug {

using events_list = std::vector<std::pair<std::chrono::duration<double>, int>>;


/**
 * \class EventLogger
 * \brief Log events since the class creation
 * \todo do not write to disk at every log
 */
class EventsLogger
{
public:
  /**
   * \brief initialize the log file and the relative timestamp
   */
  static void initialize(std::string filename);

  /**
   * \brief Add the given event to the log, with a timestamp
   * \param event Event to log
   */
  static void log(sf::Event event);

  /**
   * \brief fetch events from the replay
   * \return a list of events and their associated timestamps
   */
  static events_list fetchLoggedEvents();

  /**
   * \brief Add the given high level input to the log, with a timestamp
   * \param input input event to log
   */
  static void logProcessedEvent(e_input& input);


private:
  static std::string _logFileName; ///< log file name (may contain the path)

  static std::unique_ptr<std::ofstream> _log; ///< log file

  /// log creation timestamp
  static std::chrono::steady_clock::time_point _creationTime;
};


} //  namespace debug


#endif /* !EVENTS_LOGGER_HH_ */
