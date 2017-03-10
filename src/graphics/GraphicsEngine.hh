/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Graphics related class / functions declarations
 */

#ifndef GRAPHICS_GRAPHICS_ENGINE_HH_
# define GRAPHICS_GRAPHICS_ENGINE_HH_

# include <common/include.hh>
# include <common/using.hh> // Coords


class Map;
class Cell;
class Unit;
class Battle;
class Interface;


namespace graphics {


typedef sf::Sprite Sprite;

/**
 * \class GraphicsEngine
 * \brief Manages the display of a scene.
 */
class GraphicsEngine
{
public:
  /**
   * \brief Draws the whole scene.
   *   - calls others drawing functions
   *   - updates the window
   */
  static void drawScene(const std::shared_ptr<Battle> battle);

  /**
   * \brief Draw the interface of the current Player.
   * \note called by a State
   */
  static void drawInterface();

  /**
   * \brief _window setter.
   * \note Takes the ownership of the given unique pointer
   */
  static void setWindow(std::unique_ptr<sf::RenderWindow> window);

  /**
   * \brief Sets current fps to the given value.
   * \param fps Frame per second value.
   */
  static void setCurrentFPS(const float fps) { _currentFPS = fps; }

  /**
   * \brief Returns current number of generated frames per Seconds.
   * \return Number of fps.
   * \note If the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static auto currentFPS() { return _currentFPS; }

  static void setGridOffset(const std::shared_ptr<Map> map);

  static void closeWindow() { _window->close(); }

  static auto windowIsOpen() { return _window->isOpen(); }

  static auto pollEvent(sf::Event& event) { return _window->pollEvent(event); }


  /**
   * \brief Draws the given element
   * \param drawable shared pointer to an item to draw
   */
  template <typename T>
  static void draw(const std::shared_ptr<T> drawable) {
    _window->draw(*drawable);
  }

  /**
   * \brief Draws the given element
   * \param drawable item to draw
   */
  template <typename T>
  static void draw(const T drawable) {
    _window->draw(drawable);
  }

  /// \todo use a Window type: union with sfml, opengl, dx, ascii windows, ...
  static std::unique_ptr<sf::RenderWindow> _window; ///< graphics window


private:
  /// Draw the map background.
  static void drawBackground();

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
  static void drawUnit(const std::shared_ptr<Unit> unit);

  /**
   * \brief Draws the elements related to the given State
   */
  static void drawState();


  /**
   * \brief current number of generated frames per Seconds
   * \note if the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static float _currentFPS;
};


} // namespace graphics

#endif /* !GRAPHICS_GRAPHICS_ENGINE_HH_ */
