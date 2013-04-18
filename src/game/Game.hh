#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <game/Cursor.hh>
# include <input/Event.hh>

class Game
{
public:
  /// Ctor - Dtor
  Game();
  Game(sf::RenderWindow* window);
  ~Game();

  //void drawLine(sf::Vector2f a, sf::Vector2f b);
  int run();


private:
  sf::RenderWindow* _window;
  Event* _event;
  Map* _map;
  Cursor* _cursor;
};

#endif /* !GAME_HH_ */
