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
   * \brief log file name setter
   * \param file_name log file name (eventually with path)
   */
//  static void setFileName(std::string file_name) { _logFileName = file_name; }

  /**
   * \brief Add the given event to the log, with a timestamp
   * \param event Event to log
   */
  static void log(sf::Event event);


private:
  ///< Time elapsed since construction of the EventLogger
//  std::chrono::duration _timestamp;

  static std::string _logFileName; ///< log file name (may contain the path)

  static std::unique_ptr<std::ofstream> _log; ///< log file

  ///< log creation timestamp
  static std::chrono::steady_clock::time_point _creationTime;
};


#endif /* !EVENTS_LOGGER_HH_ */
