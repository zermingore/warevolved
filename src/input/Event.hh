#ifndef EVENT_HH_
# define EVENT_HH_

# include <input/KeyManager.hh>
# include <tools/Cursor.hh>


class Event
{
public:
  Event();
  Event(sf::RenderWindow* window, KeyManager* km, Cursor* cursor);
  ~Event();

  void process();

private:
  void game();
  void resetTimer();

  sf::RenderWindow* _window;
  sf::Event _event;
  KeyManager* _km;
  Cursor* _cursor;
};

#endif /* !EVENT_HH_ */
