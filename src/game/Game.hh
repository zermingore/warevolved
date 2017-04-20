/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 */

#ifndef GAME_HH_
# define GAME_HH_

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
   * \brief contains the game loop which calls
   *   event processing
   *   window rendering
   * \param replay true to start a replay, false otherwise
   */
  void run(bool replay);
};

#endif /* !GAME_HH_ */
