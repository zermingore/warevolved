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
   * \brief _window setter.
   */
  static void setWindow(std::unique_ptr<sf::RenderWindow> window);

  /**
   * \brief Sets current fps to the given value.
   * \param fps Frame per second value.
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

  static void setGridOffset(const std::shared_ptr<Map> map);

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
  /// Draw the map background.
  static void drawBackground();

  /**
   * \brief Draw the interface of the current Player.
   * \param battle Battle to get the current Player.
   */
  static void drawInterface(const std::shared_ptr<Battle> battle);

  /**
   * \brief Draws cells content (terrain, unit).
   * \param battle Battle content to draw.
   */
  static void drawMap(const std::shared_ptr<Battle> battle);

  /**
   * \brief Draws the grid, graphic cells separator.
   * \param Map for which we draw the grid.
   */
  static void drawGrid(const std::shared_ptr<Map> map);

  /**
   * \brief Draws the given Unit.
   * \param unit Unit to draw.
   * \param battle Battle to get the graphics properties of the current Player.
   */
  static void drawUnit(const std::shared_ptr<Battle> battle,
                       const std::shared_ptr<Unit> unit);


  /// \todo use a Window type: union with sfml, opengl, dx, ascii windows, ...
  static std::unique_ptr<sf::RenderWindow> _window;

  /**
   * \brief current number of generated frames per Seconds
   * \note if the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static float _currentFPS;
};


} // namespace graphics

#endif /* !GRAPHICSENGINE_HH_ */
