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
 * \brief Items container (backpack, trunk, pocket, ...)
 */
class ItemsContainer: public interface::InterfaceElement
{
public:
  /**
   * \brief Default contructor (parameters required)
   */
  ItemsContainer() = default;

  /**
   * \brief Contructor
   * \param type Type of the container (\see e_container_type)
   * \param name Displayed name of the container
   * \param nbCols Size of the container (in inventory cells)
   * \param nbLines Size of the container (in inventory cells)
   */
  ItemsContainer(e_container_type type,
                 const std::string& name,
                 size_t nbCols,
                 size_t nbLines);


  /**
   * \brief Update the graphics elements before drawing
   */
  virtual void update() override final;

  /**
   * \brief Draw the container and its content
   */
  virtual void draw() override final;


private:
  std::unique_ptr<graphics::Sprite> _sprite; ///< Graphic Sprite

  e_container_type _type; ///< Type of the container
  std::string _name;      ///< Displayed name

  std::vector<std::unique_ptr<Item>> _stored; ///< Items in the container

  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines;   ///< number of lines (y coordinate)
};



/**
 * \class Inventory
 * \brief Possesions of an entity (Unit, Building, Vehicle, ...)
 */
class Inventory
{
public:
  /**
   * \brief Draw the components of the Inventory (equiped list and containers)
   */
  void draw();

  /**
   * \brief Create and add a container to the Inventory
   */
  void addContainer(e_container_type type,
                    const std::string& name,
                    size_t nbCols,
                    size_t nbLines);



private:
  std::vector<std::unique_ptr<Item>> _equipped;         ///< Equiped items
  std::vector<std::unique_ptr<ItemsContainer>> _stored; ///< Stored items

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory
};


#endif /* INVENTORY_HH_ */
