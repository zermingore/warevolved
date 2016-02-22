/*
 * graphics/GraphicsEngine.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GRAPHICSENGINE_HH_
# define GRAPHICSENGINE_HH_

# include <common/include.hh>
# include <common/using.hh> // Coords


class Map;
class MapGraphicsProperties;
class Cell;
class Unit;
class Battle;
class Interface;


namespace graphics {

void initialize();


typedef sf::Sprite Sprite;

/**
   * \brief Graphics Engine class
 * manages the display of a scene
 */
class GraphicsEngine
{
public:
  /**
   * \brief Draws the whole scene
   *   - calls others drawing functions
   *   - updates the window
   */
  static void drawScene(const std::shared_ptr<Battle> battle);

  /**
   * \brief Initializes drawable zone limits
   *   by setting gridOffsets
   */
  // static void initRoom();


  /**
   * \brief _window setter
   *   updates _renderX and _renderY
   */
  static void setWindow(std::unique_ptr<sf::RenderWindow> window);

  /**
   * \brief sets current fps to the given value
   * \param fps frame per second value
   */
  static void setCurrentFPS(float fps) { _currentFPS = fps; }

  /**
   * \brief returns current number of
   *   generated frames per Seconds
   * \return number of fps
   * \note if the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static float currentFPS() { return _currentFPS; }
  static size_t cellWidth() { return _cellWidth; }
  static size_t cellHeight() { return _cellHeight; }
  static size_t gridThickness() { return _gridThickness; }
  static size_t renderX() { return _renderX; }
  static size_t renderY() { return _renderY; }
  static size_t gridOffsetX() { return _gridOffsetX; }
  static size_t gridOffsetY() { return _gridOffsetY; }


  /**
   * \brief sets cells width
   * \param width cells width
   */
  // static void setCellWidth(unsigned int width) { _cellWidth = width; }

  /**
   * \brief sets cells height
   * \param height cells height
   */
  // static void setCellHeight(unsigned int height) { _cellHeight = height; }


  /**
   * \brief sets grid thickness
   * \param thickness graphical grid thickness
   */
  // static void setGridThickness(unsigned int t) { _gridThickness = t; }

  static void setGridOffset(const std::shared_ptr<Map> map);


  /**
   * \brief sets drawable zone size width
   * \param render_x new render zone width
   */
  static void setRenderX(size_t x) { _renderX = x; }

  /**
   * \brief sets drawable zone size height
   * \param render_x new render zone height
   */
  static void setRenderY(size_t y) { _renderY = y; }

  static void closeWindow() { _window->close(); }

  static bool windowIsOpen() { return _window->isOpen(); }

  static bool pollEvent(sf::Event& event) { return _window->pollEvent(event); }

  static void draw(std::shared_ptr<Sprite> sprite)
  { _window->draw(*sprite); }

  static void draw(std::shared_ptr<sf::RectangleShape> rectangle)
  { _window->draw(*rectangle); }

  /**
   * \brief Draws the given element
   * \param drawable item to draw
   */
  template <typename T>
  static void draw(std::shared_ptr<T> drawable, Coords pos, Coords size);

  template <typename T>
  void draw(std::shared_ptr<T> drawable, Cell c);


private:
  /**
   * \brief Draws the map background
   */
  static void drawBackground();

  /**
   * \brief Draws the interface
   */
  static void drawInterface(const std::shared_ptr<Battle> battle);

  /**
   * \brief Draws cells content (terrain, unit)
   * \param battle battle content to draw
   */
  static void drawMap(const std::shared_ptr<Battle> battle);

  /**
   * \brief draws the grid, graphic cells separator
   * \param map for which we draw a grid
   */
  static void drawGrid(const std::shared_ptr<Map> map);

  /**
   * \brief Draws the given Unit
   * \param unit unit to draw
   */
  static void drawUnit(const std::shared_ptr<Battle> battle, const std::shared_ptr<Unit> unit);


   /// \todo use a Window type: union with sfml, opengl, dx, ascii windows, ...
  static std::unique_ptr<sf::RenderWindow> _window;

  /**
   * \brief current number of generated frames per Seconds
   * \note if the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static float _currentFPS;
  static size_t _cellWidth;  /// \todo dynamic, somewhere else (Map ?)
  static size_t _cellHeight;  /// \todo dynamic, somewhere else (Map ?)
  static size_t _gridThickness;
  static size_t _renderX;
  static size_t _renderY;
  static size_t _gridOffsetX;
  static size_t _gridOffsetY;
};


} // namespace graphics

#endif /* !GRAPHICSENGINE_HH_ */
