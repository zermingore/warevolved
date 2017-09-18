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

# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <interface/MiniMap.hh>

class Map;

namespace resources {
  class Image;
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
   * \brief Default constructor: call InterfaceElement constructor
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
   * \brief Origin setter
   * \param origin New panel origin
   */
  void setOrigin(const graphics::Pos2 origin) {
    _origin = origin;
  }

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


private:
  graphics::Size2 _windowSize; ///< Drawing space size

  graphics::Pos2 _origin = {0, 0}; ///< Top left or top right corner - width
  graphics::Size2 _size; ///< (A ratio of the horizontal room) x (window height)

  std::shared_ptr<const Map> _map; ///< Get terrain and unit under the Cursor
  std::shared_ptr<const Cursor> _playerCursor; ///< Used to get what is hovered

  std::unique_ptr<MiniMap> _minimap; ///< Minimap to display in its frame

  std::shared_ptr<resources::Sprite> _background;   ///< Panel's background
  std::shared_ptr<resources::Sprite> _frameCell;    ///< Hovered cell's frame
  std::shared_ptr<resources::Sprite> _frameUnit;    ///< Hovered unit's frame

  e_panel_status _status; ///< Position on the screen (Left, Right, Deactivated)
};


} // namespace interface

#endif /* !INTERFACE_PANEL_HH_ */
