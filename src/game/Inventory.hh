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
  EQUIPPED,  ///< Unit type agnostic
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
  ItemsContainer() = delete;

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
   * \brief Add the given Item to the container
   * \param item Item to add
   */
  void add(std::unique_ptr<Item> item);


  /**
   * \brief Update the graphics elements before drawing
   */
  virtual void update() override final;

  /**
   * \brief Draw the container and its content
   */
  virtual void draw() override final;


private:
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
   * \brief Default constructor. Initializes the equipped items container
   */
  Inventory();


  /**
   * \brief Draw the components of the Inventory (equipped list and containers)
   */
  void draw();

  /**
   * \brief Create and add a container to the Inventory
   * \param type Type of the container
   * \param name Displayed container name
   * \param nbCols Number of inventory cells (column)
   * \param nbLines Number of inventory cells (lines)
   */
  void addContainer(e_container_type type,
                    const std::string& name,
                    size_t nbCols,
                    size_t nbLines);

  /**
   * \brief Add a new item in the equipped list
   * \param name Displayed Item name
   * \param nbCols New Item number of used columns
   * \param nbLines New Item number of used lines
   * \note Creating a new Items from these parameters
   */
  void addEquip(const std::string& name,
                size_t nbCols,
                size_t nbLines);


private:
  std::unique_ptr<ItemsContainer> _equipped;            ///< Equipped items
  std::vector<std::unique_ptr<ItemsContainer>> _stored; ///< Stored items

  /// \todo dynamic first container place (based on biggest equipped items)
  /// Where to draw the current container
  graphics::Pos2 _currentContainerPosition = {0, 50};

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory
};


#endif /* INVENTORY_HH_ */
