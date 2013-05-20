#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <input/Event.hh>

/** \brief Game is designed to hold the whole Game and not a single game
 **   This way the Game class launches the main menu when needed
 */

class Game
{
public:
  /** \brief Default Constructor
   */
  Game();
  explicit Game(sf::RenderWindow* window);

  /** \brief Destructor
   */
  ~Game();

  /** \brief contains the game loop which calls
   **   event processing
   **   window rendering
   */
  void run();


private:
  Event* _event; ///< Events management
  Map* _map; ///< global map

  // TODO add global stack (menu, game, ...)
};

#endif /* !GAME_HH_ */
