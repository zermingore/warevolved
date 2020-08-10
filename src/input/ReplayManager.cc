/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief ReplayManager class implementation
 */

#include <debug/Debug.hh>
#include <input/KeyManager.hh>
#include <input/ReplayManager.hh>
#include <tools/StringParser.hh>
#include <config/Settings.hh>



ReplayManager::ReplayManager()
  : _mode(e_replay_mode::DEACTIVATED)
  , _creationTime(std::chrono::steady_clock::now())
{
}



void ReplayManager::prepareReplayKeys(const std::string& filename)
{
  NOTICE("Parsing replay", filename);

  char line[256];
  std::ifstream stream(filename, std::ios_base::in);
  while (stream.getline(line, 256))
  {
    if (line[0] == '#')
    {
      PRINTF("Ignoring replay comment: ", line);
      continue;
    }

    // getting the input events only from the log
    auto entry(StringParser::split(line, " "));
    if (entry.size() != 2) // not the expected format: timestamp e_key
    {
      WARNING("Skipping replay line:", line);
      continue;
    }

    auto ts = std::chrono::milliseconds{ atol(entry.front().c_str()) };
    auto key(entry[1]);
    _events[ts.count()] = atoi(key.c_str());
  }

  // Reset the clock after retrieving the events
  _creationTime = std::chrono::steady_clock::now();
}



void ReplayManager::storeKey(const e_key& key)
{
  using namespace std::chrono;
  auto time_elapsed(duration_cast<duration<double, std::milli>> (
                      steady_clock::now() - _creationTime));

  *_file << time_elapsed.count() << " " << static_cast<int> (key) << '\n';
}



void ReplayManager::setReplayFile(const std::string& filename)
{
  _filename = filename;

  _file.reset();
  _file = std::make_unique<std::ofstream> (_filename, std::ios_base::out);

  *_file << "# version " << Settings::versionString() << '\n';
}



EventsList& ReplayManager::events()
{
  if (_events.empty())
  {
    prepareReplayKeys(_filename);
  }

  return _events;
}
