#ifndef GAME_HH_
# define GAME_HH_

# include <common/include.hh>

class Game
{
public:
  /// Ctor - Dtor
  Game();
  Game(sf::RenderWindow* window);
  ~Game();

  void drawLine(sf::Vector2f a, sf::Vector2f b);
  int run();
  void manageEvents();


private:
  sf::RenderWindow* _window;
};

#endif /* !GAME_HH_ */
