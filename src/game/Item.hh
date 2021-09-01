/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Item class declaration and e_rotation enum definition
 */

#ifndef ITEM_HH_
# define ITEM_HH_

# include <cstddef> // size_t
# include <memory>
# include <string>

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>


namespace graphics {
  class Sprite;
}



/**
 * \enum e_rotation
 * \brief Possible rotations (clockwise; modulo 90 degrees)
 */
enum class e_rotation
{
  ROT_0 = 0,
  ROT_90 = 90,
  ROT_180 = 180,
  ROT_270 = 270
};



/**
 * \class Item
 * \brief Inventory Item
 */
class Item: public interface::InterfaceElement
{
public:
  /**
   * \brief Deleted default constructor (name, sprite, size required)
   */
  Item() = delete;

  /**
   * \brief Constructor
   * \param name Item displayed name
   * \param nbCols Inventory occupied space
   * \param nbLines Inventory occupied space
   * \param textureName String to fetch a Texture in order to build the Sprite
   */
  Item(const std::string& name,
       const std::string& textureName,
       size_t nbCols,
       size_t nbLines);


  /**
   * \brief Set the graphic rotation angle
   * \param rotation New rotation angle
   */
  void rotate(const e_rotation rotation);

  /// _usable getter
  bool usable() { return _usable; }

  /// _equippable getter
  bool equippable() { return _equippable; }

  /// _combinable getter
  bool combinable() { return _combinable; }

  /// Size (columns / lines) getter
  graphics::Size2 size() {
    return { static_cast<graphics::component> (_nbColumns),
             static_cast<graphics::component> (_nbLines) };
  }


  /**
   * \brief Do nothing
   */
  virtual void update() override final;

  /**
   * \brief Draw the sprite
   */
  virtual void draw() override final;



private:
  std::string _name; ///< Displayed name
  std::string _textureName; ///< Graphic Texture file name

  e_rotation _rotation = e_rotation::ROT_0; ///< Rotation in the inventory

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory

  bool _usable = false;     ///< Consumable
  bool _equippable = false; ///< Can be equipped by a Unit
  bool _combinable = false; ///< Can be combined with another Item

  std::vector<std::unique_ptr<Item>> _accessories; ///< Combined items
};


#endif /* ITEM_HH_ */
