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
# include <optional>
# include <functional>

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>


namespace graphics {
  class Sprite;
}



/**
 * \enum e_item_slot
 * \brief Describes which slot occupies the Item if equipped
 * \todo Rename -> e_item_category?
 */
enum class e_item_slot
{
  NONE,
  MAIN_WEAPON,
  SECONDARY_WEAPON, // used for counter attacks
  HEAD,
  TORSO,
  LEGS,
};



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
   * \param textureName String to fetch a Texture in order to build the Sprite
   * \param description Description text
   * \param nbCols Inventory occupied space
   * \param nbLines Inventory occupied space
   * \param slot Item category
   * \param range Item usage min, max range if applicable
   * \param onUseValue Item usage effect value (attack, heal)
   * \param use Optional callback on Item usage
   * \todo Constructor with only one parameter: Item(e_item_type)
   */
  Item(const std::string& name,
       const std::string& textureName,
       const std::string& description,
       size_t nbCols,
       size_t nbLines,
       e_item_slot slot,
       Range range,
       size_t onUseValue,
       const std::function<void()>& use = {});


  /**
   * \brief Set the graphic rotation angle
   * \param rotation New rotation angle
   */
  void rotate(const e_rotation rotation);

  /// _name getter
  auto name() const { return _name; }

  /// _usable getter
  auto usable() const { return _use != nullptr; }

  /// _equippable getter
  auto equippable() const { return _equippable; }

  /// _combinable getter
  auto combinable() const { return _combinable; }

  /// _description getter
  auto description() const { return _description; }

  /// _slot getter
  auto slot() const { return _slot; }

  /// _onUseValue getter
  auto onUseValue() const { return _onUseValue; }

  /// _range getter
  auto range() const { return _range; }

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


  /**
   * \brief _use callback setter
   * \param callback Callback called when the item is used
   */
  void setUseCallback(const std::function<void()> callback) {
    _use = callback;
  }

  /**
   * \brief _use() function wrapper
   */
  void use() { _use(); }



private:
  std::string _name; ///< Displayed name
  std::string _textureName; ///< Graphic Texture file name
  std::string _description; ///< Item description text

  e_rotation _rotation = e_rotation::ROT_0; ///< Rotation in the inventory

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory

  /// \todo type based
  bool _equippable = true; ///< Can be equipped by a Unit
  bool _combinable = false; ///< Can be combined with another Item

  std::vector<std::unique_ptr<Item>> _accessories; ///< Combined items
  std::function<void()> _use; ///< Callback on item usage

  size_t _valueEquipped; ///< Value if the Item if equipped (protections)

  e_item_slot _slot; ///< Item slot (if equipped)

  /// Effect range (minimum / maximum, in Cells)
  Range _range;

  size_t _onUseValue; ///< Usage effect value
};


#endif /* ITEM_HH_ */
