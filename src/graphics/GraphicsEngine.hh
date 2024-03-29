/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \namespace graphics
 * \brief GraphicsEngine class declaration
 */

#ifndef GRAPHICS_GRAPHICS_ENGINE_HH_
# define GRAPHICS_GRAPHICS_ENGINE_HH_

# include <memory>
# include <mutex>

# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>

# include <graphics/graphic_types.hh>
# include <game/TerrainsHandler.hh>


class Map;
class Cell;
class Unit;
class Battle;
class Interface;
class TerrainsHandler;



namespace graphics {



/**
 * \class GraphicsEngine
 * \brief Manages the display of the scene
 */
class GraphicsEngine
{
public:
  /**
   * \brief Draws the whole scene.
   *   - calls others drawing functions
   *   - updates the window
   * \note Drawing while the window is not closed
   */
  static void drawScene(const std::shared_ptr<Battle>& battle);

  /**
   * \brief Draw the interface of the current Player.
   * \note called by a State
   */
  static void drawInterface();

  /**
   * \brief _window setter. Disable the screenshot request, if any
   *   (used for initialization)
   * \note Takes the ownership of the given unique pointer
   */
  static void setWindow(std::unique_ptr<RenderWindow> window) {
    _window = std::move(window);
    _takeScreenshot = false;
  }

  /**
   * \brief Set the offset between the window border and the grid
   * \param map Used to get the number of columns and lines of the map
   */
  static void setGridOffset(const std::shared_ptr<const Map>& map);

  /**
   * \brief Close the window on request; exiting the main loop
   * \note does not return
   */
  [[ noreturn ]] static void exitRequest();

  /**
   * \brief Return the next event on the window if any
   */
  static auto pollEvent(sf::Event& event) {
    return _window->pollEvent(event);
  }

  /**
   * \brief Window size getter
   */
  static auto windowSize() {
    return _window->getSize();
  }

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

  /**
   * \brief Only performs a screenshot request
   *   The boolean is check at each frame (instead of locking the window)
   */
  static void screenshotRequest() {
    _takeScreenshot = true;
  }

  /**
   * \brief Resize the rendered view when the window get resized
   * \param width New window width
   * \param height New window height
   */
  static void resizeWindow(unsigned int width, unsigned int height);


private:
  /**
   * \brief Draw the map background
   */
  static void drawBackground();

  /**
   * \brief Draws cells content (terrain, unit).
   * \param battle Battle content to draw.
   */
  static void drawMap(const std::shared_ptr<Battle>& battle);

  /**
   * \brief Draws the grid, graphic cells separator.
   * \param map for which we draw the grid.
   */
  static void drawGrid(const std::shared_ptr<Map>& map);

  /**
   * \brief Draws the given Unit.
   * \param unit Unit to draw.
   */
  static void drawUnit(const std::shared_ptr<Unit>& unit);

  /**
   * \brief Draws the elements related to the given State
   */
  static void drawState();

  /**
   * \brief Save the current rendered image to a file
   */
  static void screenshot();


  inline static std::unique_ptr<sf::RenderWindow> _window; ///< graphics window
  inline static bool _exit;           ///< true: got request to quit
  inline static bool _takeScreenshot; ///< true when a screenshot is requested

  /// Terrains list
  inline static std::unique_ptr<TerrainsHandler> _terrainsHandler;
};



} // namespace graphics

#endif /* !GRAPHICS_GRAPHICS_ENGINE_HH_ */
