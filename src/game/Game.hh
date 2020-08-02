/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Game class declaration
 */

#ifndef GAME_HH_
# define GAME_HH_

# include <string>
# include <vector>
# include <optional>


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
   * \param options_parser Command line options parser
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
   * \note Create EventsProcessor and InputsListener threads
   */
  void run();


private:
  const OptionsParser& _optionsParser;
  bool _replay = false;
  mutable std::vector<std::string> _replayFiles;
};

#endif /* !GAME_HH_ */
