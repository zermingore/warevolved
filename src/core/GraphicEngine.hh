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

  void drawScene();


private:
  void drawMap();
  void drawPanel();
  void drawMenuBar();

  /// draws cell content (terrain, unit)
  void drawCells();

  /// in case there are too many cells to display
  void drawGrid();
  void drawGrid(unsigned int nb_line, unsigned int nb_column);

  void drawCursor();

  sf::RenderWindow* _window;
  Cursor* _cursor;

  // space left for rendering
  unsigned int _renderX;
  unsigned int _renderY;

  int _gridOffsetX; // in px
  int _gridOffsetY; // in px
};

#endif /* !GRAPHICENGINE_HH_ */
