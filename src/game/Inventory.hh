/**
 * \file
 * \date December 11, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes declaration
 */

#ifndef INVENTORY_HH_
# define INVENTORY_HH_

# include <cstddef> // size_t
# include <memory>
# include <string>

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>


namespace graphics {
  class Sprite;
}

class Item;



enum class e_container_type
{
  BACKPACK, ///< Soldier only
  POCKET,   ///< Soldier only
  TRUNK,    ///< Vehicle only
};



/**
 * \class ItemsContainer
 * \brief Items Container (backpack, trunk, pocket, ...)
 */
class ItemsContainer
{
public:
  /**
   * \brief Default contructor (name required)
   */
  ItemsContainer() = default;

  /**
   * \brief Contructor (name required)
   */
  ItemsContainer(e_container_type type,
                 const std::string& name,
                 const std::string& textureName);


private:
  e_container_type _type; ///< Type of the container
  std::string _name;      ///< Displayed name

  std::string _textureName;                  ///< Graphic Texture file name
  std::unique_ptr<graphics::Sprite> _sprite; ///< Graphic Sprite

  std::vector<std::unique_ptr<Item>> _stored; ///< Items in the container
};



/**
 * \class Inventory
 * \brief Possesions of an entity (Unit, Building, Vehicle, ...)
 */
class Inventory: public interface::InterfaceElement
{
public:
  /**
   * \brief Deleted default constructor (size required)
   */
  Inventory() = delete;

  /**
   * \brief Constructor
   * \param nbCols Inventory occupied space
   * \param nbLines Inventory occupied space
   */
  Inventory(size_t nbCols, size_t nbLines);


  /**
   * \brief Update the graphics elements before drawing
   */
  virtual void update() override final;

  /**
   * \brief Draw the components of the Inventory
   */
  virtual void draw() override final;


private:
  std::unique_ptr<graphics::Sprite> _sprite; ///< Graphic Sprite

  std::vector<std::unique_ptr<Item>> _equipped;         ///< Equiped items
  std::vector<std::unique_ptr<ItemsContainer>> _stored; ///< Stored items

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory
};


#endif /* INVENTORY_HH_ */
