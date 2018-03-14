/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class declaration
 */


#ifndef INTERFACE_PANEL_HH_
# define INTERFACE_PANEL_HH_

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>
# include <common/enums/panel_status.hh>
# include <graphics/Sprite.hh>

# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <interface/MiniMap.hh>

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
   * \brief Add some informative text related to the hovered Unit
   * \param content Text to append tho the _unitDataText buffer
   * \note This function draws nothing, it just buffers the given string
   * \see drawUnitData
   */
  void addUnitData(const std::string content);


  /**
   * \brief Draw the buffered Unit data
   * \note clear the _unitDataText buffer
   */
  void drawUnitData();


  /**
   * \brief Draw meta-information (fps, time, ...)
   */
  void drawMetaInfo();



private:
  graphics::Size2 _windowSize; ///< Drawing space size

  const graphics::component _margin = 5;
  graphics::Size2 _size; ///< (A ratio of the horizontal room) x (window height)

  std::shared_ptr<const Map> _map; ///< Get terrain and unit under the Cursor
  std::shared_ptr<const Cursor> _playerCursor; ///< Used to get what is hovered

  std::unique_ptr<MiniMap> _minimap; ///< Minimap to display in its frame

  std::unique_ptr<graphics::Sprite> _background; ///< Panel's background
  std::unique_ptr<graphics::Sprite> _frameCell;  ///< Hovered cell's frame
  std::unique_ptr<graphics::Sprite> _frameUnit;  ///< Hovered unit's frame

  e_panel_status _status; ///< Position on the screen (Left, Right, Deactivated)

  size_t _fontSize;            ///< Text font size (for the Unit HP, ...)
  graphics::Pos2 _unitDataPos; ///< Unit data text position (top-left corner)
  std::string _unitDataText;   ///< Unit data text content

  graphics::Pos2 _metaInfoPos;    ///< Meta-info position (fps, ...)
  graphics::component _dateWidth; ///< Date width, in pixels
  graphics::component _fpsWidth;  ///< Fps frame width, in pixels
};


} // namespace interface

#endif /* !INTERFACE_PANEL_HH_ */
