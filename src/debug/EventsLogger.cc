#include <debug/EventsLogger.hh>
#include <fstream>
#include <chrono>

// static attributes definition
std::string EventsLogger::_logFileName;
std::unique_ptr<std::ofstream> EventsLogger::_log;
std::chrono::steady_clock::time_point EventsLogger::_creationTime;


void EventsLogger::initialize(std::string filename)
{
  _log = std::make_unique<std::ofstream> (filename, std::ios_base::out);

  time_t now = time(0);
  struct tm *full_date = localtime(&now);
  char buf[80] = {0};
  strftime(buf, 80, "%Y-%m-%d @ %T", full_date); // building date
  *_log << "Event log created on: " << buf << '\n';

  _creationTime = std::chrono::steady_clock::now();
}


void EventsLogger::log(sf::Event event)
{
  std::chrono::duration<double> time_elapsed(std::chrono::steady_clock::now() - _creationTime);
  *_log << time_elapsed.count() << "| " << static_cast<int> (event.type) << '\n';
}
