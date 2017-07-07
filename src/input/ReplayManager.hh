#ifndef REPLAY_MANAGER_HH_
# define REPLAY_MANAGER_HH_

# include <utility>
# include <vector>
# include <string>
# include <memory>
# include <fstream>
# include <chrono>

enum class e_key;


using EventsList = std::vector<std::pair<std::chrono::duration<double>, int>>;

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

  ~ReplayManager() = default; /// \todo flush / make sure the file is closed


  /// List of events recorded during a previous game
  void prepareReplayKeys(const std::string&);

  void storeKey(const e_key& key);

  /**
   * \brief _mode getter
   */
  e_replay_mode mode() const;

  /**
   * \brief _mode setter
   */
  void setMode(const e_replay_mode mode);

  /**
   * \brief Set the replay filename, reset the open stream using this filename
   * \param filename File name to open
   */
  void setReplayFile(const std::string& filename);

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

  EventsList _events;
};


#endif /* !REPLAY_MANAGER_HH_ */
