/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 */

#ifndef GAME_HH_
# define GAME_HH_

# include <string>
# include <vector>


class OptionsParser;


/**
 * \class Game
 * \brief Game is designed to hold the whole Game and not a single game.
 *
 * This way the Game class launches the main menu when needed.
 */
class Game
{
public:
  /**
   * \brief Deleted default constructor: the options are required
   */
  Game() = delete;

  /**
   * \brief Initializes the graphical context
   * \param fullscreen Initialize a full screen or windowed graphical context
   * \see Context
   */
  explicit Game(const OptionsParser& options_parser);

  /**
   * \brief Defaulted destructor: the Context doesn't need to be deleted
   */
  ~Game() = default;


  /**
   * \brief contains the game loop which calls
   *   event processing
   *   window rendering
   * \param replay true to start a replay, false otherwise
   * \param filename Replay filename to read
   */
  void run();


private:
  const OptionsParser& _optionsParser;
  const std::vector<std::string> _replayFiles;
};

#endif /* !GAME_HH_ */
