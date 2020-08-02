/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \namespace interface
 * \brief Side panel's MiniMap class declaration
 */


#ifndef INTERFACE_MINIMAP_HH_
# define INTERFACE_MINIMAP_HH_

# include <memory>
# include <vector>
# include <utility>

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>
# include <common/using.hh>

class Map;


namespace interface {

class Cursor;


/**
 * \class MiniMap
 * \brief In charge of the build / display of the minimap in the side panel
 */
class MiniMap final: public InterfaceElement
{
public:
  /**
   * \brief Constructor: needs the Map and Cursor to check what is hovered
   * \param size Minimap's frame size
   * \param map Game's map
   * \param cursor Cursor of the player (needed to put a mark on the minimap)
   */
  MiniMap(const graphics::Size2& size,
          const std::shared_ptr<const Map>& map,
          const std::shared_ptr<const Cursor>& cursor);

  /**
   * \brief Update the minimap content
   * \todo Don't rebuild the minimap if the map / cursor position didn't change
   */
  void update() override final;

  /**
   * \brief Draw the minimap in the side panel
   */
  void draw() override final;


  /**
   * \brief Set the MiniMap position
   * \param pos New position
   */
  void setPosition(const graphics::Pos2& pos);

  /**
   * \brief Set the MiniMap frame size
   * \param size New size
   */
  void setFrameSize(const graphics::Size2& size);



private:
  graphics::Size2 _frameSize; ///< Draw area size

  const Map& _map; ///< Pointer on the game's map

  /// The cursor's position is displayed on the minimap
  const Cursor& _playerCursor;
};


} // namespace interface


#endif /* !INTERFACE_MINIMAP_HH_ */
