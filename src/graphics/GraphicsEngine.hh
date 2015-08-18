/*
 * graphics/GraphicsEngine.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GRAPHICSENGINE_HH_
# define GRAPHICSENGINE_HH_

# include <common/include.hh>
# include <game/Map.hh>


namespace graphics {

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
  static void drawScene(const std::shared_ptr<Map> map);

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
  static inline unsigned int cellWidth() { return _cellWidth; }
  static inline unsigned int cellHeight() { return _cellHeight; }
  static inline unsigned int gridThickness() { return _gridThickness; }
  static inline unsigned int renderX() { return _renderX; }
  static inline unsigned int renderY() { return _renderY; }
  static inline unsigned int gridOffsetX() { return _gridOffsetX; }
  static inline unsigned int gridOffsetY() { return _gridOffsetY; }


  /** \brief sets cells width
   ** \param width cells width
   */
  static inline void setCellWidth(unsigned int width) { _cellWidth = width; }

  /** \brief sets cells height
   ** \param height cells height
   */
  static inline void setCellHeight(unsigned int height) { _cellHeight = height; }


  /** \brief sets grid thickness
   ** \param thickness graphical grid thickness
   */
  static inline void setGridThickness(unsigned int t) { _gridThickness = t; }

  static inline void setGridOffset(const std::shared_ptr<Map> map);


  /** \brief sets drawable zone size width
   ** \param render_x new render zone width
   */
  static inline void setRenderX(unsigned int x) { _renderX = x; }

  /** \brief sets drawable zone size height
   ** \param render_x new render zone height
   */
  static inline void setRenderY(unsigned int y) { _renderY = y; }

  static inline void draw(std::shared_ptr<Sprite> sprite)
  { _window->draw(*sprite); }

  static inline void draw(std::shared_ptr<sf::RectangleShape> rectangle)
  { _window->draw(*rectangle); }

  static inline void closeWindow() { _window->close(); }

  static inline bool windowIsOpen() { return _window->isOpen(); }

  static inline bool pollEvent(sf::Event& event) { return _window->pollEvent(event); }



private:
  /** \brief Draws the map background
   */
  static void drawBackground();

  /** \brief Draws cell content (terrain, unit)
   ** \param map map content to draw
   */
  static void drawMap(const std::shared_ptr<Map> map);

  /** \brief draws the grid, graphic cells separator
   ** \param map for which we draw a grid
   */
  static void drawGrid(const std::shared_ptr<Map> map);

  /** \brief Draws the given Unit
   ** \param unit unit to draw
   */
  static void drawUnit(const std::shared_ptr<Unit> unit);



  // TODO use a Window type: union with sfml, opengl, dx, ascii windows, ...
  static std::unique_ptr<sf::RenderWindow> _window;

  /** \brief current number of generated frames per Seconds
   ** \note if the compilation flag DEBUG_PERFS is not set
   **   the frame rate will be limited to 60
   **   it will be unlimited otherwise
   */
  static float _currentFPS;
  static unsigned int _cellWidth; // TODO dynamic, somewhere else (Map ?)
  static unsigned int _cellHeight; // TODO dynamic, somewhere else (Map ?)
  static unsigned int _gridThickness;
  static unsigned int _renderX;
  static unsigned int _renderY;
  static unsigned int _gridOffsetX;
  static unsigned int _gridOffsetY;
};


} // namespace graphics

#endif /* !GRAPHICSENGINE_HH_ */
