/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side Panel class declaration and enum e_panel_status definition
 */


#ifndef INTERFACE_PANEL_HH_
# define INTERFACE_PANEL_HH_

# include <interface/Cursor.hh>
# include <interface/MiniMap.hh>

# include <graphics/graphic_types.hh>
# include <graphics/Sprite.hh>
# include <interface/InterfaceElement.hh>
# include <game/Map.hh>


enum class e_panel_status; // definition follows

class Map;

namespace resources {
  class Text;
}


namespace interface {

class Cursor;


/**
 * \class Panel
 * \brief Side panel class,
 *   where the minimap and hovered cell data are displayed
 */
class Panel: public InterfaceElement
{
public:
  /**
   * \brief Deleted default constructor: The Map and Cursor are required
   */
  Panel() = delete;

  /**
   * \brief Constructor: needs the Map and Cursor to check what is hovered
   * \param map Game's map
   * \param cursor Cursor of the player (the interface owner)
   */
  Panel(std::shared_ptr<const Map> map, std::shared_ptr<const Cursor> cursor);


  /**
   * \brief Toggle the side panel status (Left, Right, Deactivated)
   */
  void toggleStatus();

  /**
   * \brief Computes the panel new position
   * \note Called on window redraw or pannel activation
   */
  void computePosition();

  /**
   * \brief Updates the window size
   *   Updates the Panel components size accordingly
   */
  void setWindowSize(const graphics::Size2& size);


  /**
   * \brief Update the panel before drawing
   */
  virtual void update() override final;


  /**
   * \brief Draw the components of the panel
   */
  virtual void draw() override final;


  /**
   * \brief Draw the given data
   * \param data Text data to display
   * \param pos Position where to draw
   */
  void drawDataText(const std::string& data, const graphics::Pos2& pos);


  /**
   * \brief Draw the given data
   * \param data Text data to display
   * \param pos Position where to draw
   * \param size Text size
   */
  void drawDataText(const std::string& data,
                    const graphics::Pos2& pos,
                    size_t size);



private:
  /**
   * \brief Draw the Terrain under current cursor position and its data
   */
  void drawTerrainFrame();

  /**
   * \brief Draw the Unit under current cursor position and its data
   */
  void drawUnitFrame();

  /**
   * \brief Draw the concerned unit's crew
   */
  void drawCrew();

  /**
   * \brief Draw meta-information (fps, time, ...)
   */
  void drawMetaInfo();

  /**
   * \brief Draw selected Unit's Inventory
   */
  void drawEquippedItems();


  const graphics::component _margin = 5; ///< Graphic margin (in px)
  graphics::Size2 _size; ///< (A ratio of the horizontal room) x (window height)

  std::shared_ptr<const Map> _map; ///< Get terrain and unit under the Cursor
  std::shared_ptr<const Cursor> _playerCursor; ///< Used to get what is hovered

  std::unique_ptr<MiniMap> _minimap; ///< Minimap to display in its frame

  std::unique_ptr<graphics::Sprite> _background; ///< Panel's background
  std::unique_ptr<graphics::Sprite> _frameCell;  ///< Hovered cell's frame
  std::unique_ptr<graphics::Sprite> _frameUnit;  ///< Hovered unit's frame

  e_panel_status _status; ///< Position on the screen (Left, Right, Deactivated)

  size_t _fontSize;               ///< Text font size (for the Unit HP, ...)
  graphics::Pos2 _unitDataPos;    ///< Unit data text position (top-left corner)
  graphics::Pos2 _terrainDataPos; ///< Terrain data text position

  graphics::Pos2 _metaInfoPos;    ///< Meta-info position (fps, ...)
  graphics::component _dateWidth; ///< Date width, in pixels
};


} // namespace interface


/**
 * \enum e_panel_status
 * \brief List the possible locations of the interface side panel
 */
enum class e_panel_status
{
  DEACTIVATED = 0,
  POSITION_LEFT,
  POSITION_RIGHT,

  NB_PANEL_STATUS
};


#endif /* !INTERFACE_PANEL_HH_ */
