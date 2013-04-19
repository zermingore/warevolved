#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <game/Cursor.hh>
# include <input/Event.hh>

/** \brief Game is designed to hold the whole Game and not a single game
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
  sf::RenderWindow* _window;
  Event* _event;
  Map* _map;
};

#endif /* !GAME_HH_ */
