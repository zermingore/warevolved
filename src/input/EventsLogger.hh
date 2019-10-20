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



using events_list = std::vector<std::pair<std::chrono::duration<double>, int>>;


/**
 * \class EventLogger
 * \brief Log events since the class creation
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


private:
  static std::string _logFileName; ///< log file name (may contain the path)

  static std::unique_ptr<std::ofstream> _log; ///< log file

  /// log creation timestamp
  static std::chrono::steady_clock::time_point _creationTime;
};


#endif /* !EVENTS_LOGGER_HH_ */