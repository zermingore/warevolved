/*
 * game/Game.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GAME_HH_
# define GAME_HH_

# include <input/Event.hh>
# include <game/applications/Application.hh>


/** \brief Game is designed to hold the whole Game and not a single game
 **   This way the Game class launches the main menu when needed
 */
class Game
{
public:
  /** \brief Default Constructor
   */
  Game();

  /** \brief Destructor
   */
  ~Game();

  /** \brief contains the game loop which calls
   **   event processing
   **   window rendering
   */
  void run();


private:
  Event *_event; ///< Events management
  Application *_currentApplication;
};

#endif /* !GAME_HH_ */
