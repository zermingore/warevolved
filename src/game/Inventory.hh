/**
 * \file
 * \date December 11, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes declaration
 */

#ifndef Inventory_HH_
# define Inventory_HH_

# include <cstddef> // size_t
# include <memory>
# include <string>

# include <graphics/graphic_types.hh>


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
  std::shared_ptr<graphics::Sprite> _sprite; ///< Graphic Sprite

  std::vector<std::unique_ptr<Item>> _stored; ///< Items in the container
};



/**
 * \class Inventory
 * \brief Possesions of an entity (Unit, Building, Vehicle, ...)
 */
class Inventory
{
public:
  /**
   * \brief Deleted default constructor (name, sprite, size required)
   */
  Inventory() = delete;

  /**
   * \brief Constructor
   * \param nbCols Inventory occupied space
   * \param nbLines Inventory occupied space
   */
  Inventory(size_t nbCols, size_t nbLines);


private:
  std::string _textureName;                  ///< Graphic Texture file name
  std::shared_ptr<graphics::Sprite> _sprite; ///< Graphic Sprite

  std::vector<std::unique_ptr<Item>> _equipped; ///< Equiped items

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory
};


#endif /* Inventory_HH_ */
