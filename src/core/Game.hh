#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>
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
  Cursor* _cursor;
};

#endif /* !GAME_HH_ */
