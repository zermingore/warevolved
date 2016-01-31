/*
 * graphics/GraphicsEngine.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GRAPHICSENGINE_HH_
# define GRAPHICSENGINE_HH_

# include <common/include.hh>

class Map;
class MapGraphicsProperties;
class Cell;
class Unit;
class Battle;
class Interface;


namespace graphics {

void initialize();


typedef sf::Sprite Sprite;

/** \brief Graphics Engine class
 ** manages the display of a scene
 */
class GraphicsEngine
{
public:
  /** \brief Draws the whole scene
   **   - calls others drawing functions
   **   - updates the window
   */
  static void drawScene(const std::shared_ptr<Battle> battle);

  /** \brief Initializes drawable zone limits
   **   by setting gridOffsets
   */
  // static void initRoom();


  /** \brief _window setter
   **   updates _renderX and _renderY
   */
  static void setWindow(std::unique_ptr<sf::RenderWindow> window);

  /** \brief sets current fps to the given value
   ** \param fps frame per second value
   */
  static inline void setCurrentFPS(float fps) { _currentFPS = fps; }

  /** \brief returns current number of
   **   generated frames per Seconds
   ** \return number of fps
   ** \note if the compilation flag DEBUG_PERFS is not set
   **   the frame rate will be limited to 60
   **   it will be unlimited otherwise
   */
  static inline float currentFPS() { return _currentFPS; }
  static inline size_t cellWidth() { return _cellWidth; }
  static inline size_t cellHeight() { return _cellHeight; }
  static inline size_t gridThickness() { return _gridThickness; }
  static inline size_t renderX() { return _renderX; }
  static inline size_t renderY() { return _renderY; }
  static inline size_t gridOffsetX() { return _gridOffsetX; }
  static inline size_t gridOffsetY() { return _gridOffsetY; }


  /** \brief sets cells width
   ** \param width cells width
   */
  // static inline void setCellWidth(unsigned int width) { _cellWidth = width; }

  /** \brief sets cells height
   ** \param height cells height
   */
  // static inline void setCellHeight(unsigned int height) { _cellHeight = height; }


  /** \brief sets grid thickness
   ** \param thickness graphical grid thickness
   */
  // static inline void setGridThickness(unsigned int t) { _gridThickness = t; }

  static inline void setGridOffset(const std::shared_ptr<Map> map);


  /** \brief sets drawable zone size width
   ** \param render_x new render zone width
   */
  static inline void setRenderX(size_t x) { _renderX = x; }

  /** \brief sets drawable zone size height
   ** \param render_x new render zone height
   */
  static inline void setRenderY(size_t y) { _renderY = y; }

  static inline void closeWindow() { _window->close(); }

  static inline bool windowIsOpen() { return _window->isOpen(); }

  static inline bool pollEvent(sf::Event& event) { return _window->pollEvent(event); }

  static inline void draw(std::shared_ptr<Sprite> sprite)
  { _window->draw(*sprite); }

  static inline void draw(std::shared_ptr<sf::RectangleShape> rectangle)
  { _window->draw(*rectangle); }

  /** \brief Draws the given element
   ** \param drawable item to draw
   */
  template <class T>
  static void draw(std::shared_ptr<T> drawable, Coords pos, Coords size);

  template <class T>
  void draw(std::shared_ptr<T> drawable, Cell c);


private:
  /** \brief Draws the map background
   */
  static void drawBackground();

  /** \brief Draws the interface
   */
  static void drawInterface(const std::shared_ptr<Interface> interface);

  /** \brief Draws cells content (terrain, unit)
   ** \param battle battle content to draw
   */
  static void drawMap(const std::shared_ptr<Battle> battle);

  /** \brief draws the grid, graphic cells separator
   ** \param map for which we draw a grid
   */
  static void drawGrid(const std::shared_ptr<Map> map);

  /** \brief Draws the given Unit
   ** \param unit unit to draw
   */
  static void drawUnit(const std::shared_ptr<Battle> battle, const std::shared_ptr<Unit> unit);


  // TODO use a Window type: union with sfml, opengl, dx, ascii windows, ...
  static std::unique_ptr<sf::RenderWindow> _window;

  /** \brief current number of generated frames per Seconds
   ** \note if the compilation flag DEBUG_PERFS is not set
   **   the frame rate will be limited to 60
   **   it will be unlimited otherwise
   */
  static float _currentFPS;
  static size_t _cellWidth; // TODO dynamic, somewhere else (Map ?)
  static size_t _cellHeight; // TODO dynamic, somewhere else (Map ?)
  static size_t _gridThickness;
  static size_t _renderX;
  static size_t _renderY;
  static size_t _gridOffsetX;
  static size_t _gridOffsetY;
};


} // namespace graphics

#endif /* !GRAPHICSENGINE_HH_ */
