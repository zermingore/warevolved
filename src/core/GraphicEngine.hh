#ifndef GRAPHICENGINE_HH_
# define GRAPHICENGINE_HH_

# include <common/include.hh>
# include <common/Settings.hh>
# include <tools/Cursor.hh>


class GraphicEngine
{
public:
  GraphicEngine();
  GraphicEngine(sf::RenderWindow* window, Cursor* cursor);
  ~GraphicEngine();

  /// in case there are too many cells to display
  void drawGrid();
  void drawGrid(unsigned int nb_line, unsigned int nb_column);

private:
  sf::RenderWindow* _window;
  Cursor* _cursor;
};

#endif /* !GRAPHICENGINE_HH_ */
