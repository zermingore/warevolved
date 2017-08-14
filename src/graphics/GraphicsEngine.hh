/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Graphics related class / functions declarations
 */

#ifndef GRAPHICS_GRAPHICS_ENGINE_HH_
# define GRAPHICS_GRAPHICS_ENGINE_HH_

# include <memory>
# include <mutex>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>

# include <graphics/graphic_types.hh>

class Map;
class Cell;
class Unit;
class Battle;
class Interface;


namespace graphics {


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
  static void setWindow(std::unique_ptr<RenderWindow> window);

  static void setGridOffset(const std::shared_ptr<Map> map);

  static void closeWindow() { _window->close(); }

  static auto windowIsOpen() { return _window->isOpen(); }

  static auto waitEvent(sf::Event& event) { return _window->waitEvent(event); }


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

  static std::unique_ptr<RenderWindow> _window; ///< graphics window


  /**
   * \brief Save the current rendered image to a file
   */
  static void screenshot();


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
   * \brief current number of generated frames
   * \note if the compilation flag DEBUG_PERFS is not set
   *   the frame rate will be limited to 60
   *   it will be unlimited otherwise
   */
  static size_t _nbFramesGenerated;


  static std::mutex mutexRenderWindow;
};


} // namespace graphics

#endif /* !GRAPHICS_GRAPHICS_ENGINE_HH_ */
