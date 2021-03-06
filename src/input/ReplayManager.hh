/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief Records replay files and retrieve the written events
 */

#ifndef REPLAY_MANAGER_HH_
# define REPLAY_MANAGER_HH_

# include <map>
# include <string>
# include <memory>
# include <fstream>
# include <chrono>

enum class e_key;


/// EventsList is a map of timestamp, key pressed
using EventsList = std::map<long int, int>;

enum class e_replay_mode: int8_t
{
  DEACTIVATED = 0,
  RECORD,
  READ
};


/**
 * \class ReplayManager
 * \brief Handle game replays recording and replaying events
 */
class ReplayManager
{
public:
  /**
   * \brief Default constructor. Initializes the replay clock
   */
  ReplayManager();

  /**
   * \brief Default destructor
   * \todo flush / make sure the file is closed
   */
  ~ReplayManager() = default;


  /// List of events recorded during a previous game
  void prepareReplayKeys(const std::string&);

  /**
   * \brief Register the given key in the replay file
   * \param key Key to add to the replay file
   */
  void storeKey(const e_key& key);

  /**
   * \brief _mode getter
   */
  e_replay_mode mode() const { return _mode; }

  /**
   * \brief _mode setter
   */
  void setMode(const e_replay_mode mode) { _mode = mode; }

  /**
   * \brief Set the replay filename, reset the open stream using this filename
   * \param filename File name to open
   * \param header Comments header (random seed / map load file)
   */
  void setReplayFile(const std::string& filename, const std::string& header);

  /**
   * \brief Builds if necessary and return the list of events from the replay
   * \return List of events retrieved from the replay file
   */
  EventsList& events();


private:
  e_replay_mode _mode; ///< Record or read

  std::string _filename; ///< Replay file name
  std::unique_ptr<std::ofstream> _file; ///< File associated with this replay

  /// Replay file creation time
  std::chrono::steady_clock::time_point _creationTime;

  EventsList _events; ///< List of events extracted from the replay
};


#endif /* !REPLAY_MANAGER_HH_ */
