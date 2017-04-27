#include <fstream>
#include <chrono>
#include <map>

#include <debug/Debug.hh>
#include <debug/EventsLogger.hh>
#include <generated/enum_print/enum_print_prototypes.hh>

#include <tools/StringParser.hh>


namespace debug {

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


events_list EventsLogger::fetchEventsReplay()
{
  auto filename("test_log");

  // list of events, with timestamps
  events_list recorded_events;

  char line[256];
  std::ifstream stream(filename, std::ios_base::in);
  while (stream.getline(line, 256))
  {
    // getting the input events only from the log
    auto entry(StringParser::split(line, " \\| input:"));
    if (entry.size() == 1) // no result
    {
      std::cerr << "skipping line: " << line << std::endl;
      continue;
    }

    auto timestamp(std::chrono::duration<double> (atof(entry.front().c_str())));
    auto input(StringParser::split(entry[1], "val="));
    if (input.size() < 2)
    {
      std::cerr << "input malformed: expected input: val=x str=x" << std::endl;
      continue;
    }

    // everything between the '=' and ' ' is the value
    auto value(StringParser::split(input[1], " ")[0]);

    recorded_events.push_back({timestamp, atof(value.c_str())});
    std::cout << "input: @" << timestamp.count()
              << ": " << recorded_events.back().second << std::endl;
  }

  return recorded_events;
}


void EventsLogger::log(sf::Event event)
{
  // checking for initialization \todo no longer static class
  if (!_log)
  {
    ERROR("log not initialized");
    return;
  }

  auto time_elapsed(std::chrono::steady_clock::now() - _creationTime);
  *_log << time_elapsed.count()
        << " | event type: " << static_cast<int> (event.type) << '\n';
}


void EventsLogger::logProcessedEvent(e_input input)
{
  // checking for initialization \todo no longer static class
  if (!_log)
  {
    ERROR("log not initialized");
    return;
  }

  auto time_elapsed(std::chrono::steady_clock::now() - _creationTime);
  *_log << time_elapsed.count() << "| input:"
        << " val=" << static_cast<int> (input)
        << " str=" << e_input_string(input) << '\n';
}


} // namespace debug
