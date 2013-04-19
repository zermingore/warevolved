#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <game/Cursor.hh>
# include <input/Event.hh>

class Game
{
public:
  /** \
   */
  Game();
  explicit Game(sf::RenderWindow* window);
  ~Game();

  int run();


private:
  sf::RenderWindow* _window;
  Event* _event;
  Map* _map;
  Cursor* _cursor;
};

#endif /* !GAME_HH_ */
