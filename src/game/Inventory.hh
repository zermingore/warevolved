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
# include <game/Item.hh>
# include <game/PathFinding.hh> // e_directions -> TODO split


namespace graphics {
  class Sprite;
}

namespace resources {
  class Text;
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
  bool add(std::unique_ptr<Item> item);

  /***
   * \brief Select the next item, according to the given direction
   */
  void selectItem(const e_direction direction);

  /**
   * \brief Update the graphics elements before drawing
   */
  virtual void update() override final;

  /**
   * \brief Draw the container and its content
   */
  virtual void draw() override final;

  ///< _selected getter
  /// \todo rename getter or attribute?
  auto selectedItemCoords() const { return _selected; }


private:
  e_container_type _type; ///< Type of the container
  std::string _name;      ///< Displayed name

  /// Items in the container and their coordinates in the container
  std::vector<std::pair<Coords, std::unique_ptr<Item>>> _stored;

  size_t _nbColumns; ///< Number of columns (x coordinate)
  size_t _nbLines;   ///< Number of lines (y coordinate)

  std::vector<bool> _freeCells; ///< Keeping track of free space

  Coords _selected; ///< Selected item location

  std::shared_ptr<resources::Text> _label; ///< button label text
  std::shared_ptr<resources::Text> _labelDescription; ///< description text
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
   * \param description New Item description
   * \param nbCols New Item number of used columns
   * \param nbLines New Item number of used lines
   * \return true on success; false on impossible add (item too large)
   * \note Creating a new Items from these parameters
   * \todo only one paramter to take and forward: item type
   */
  bool addEquip(const std::string& name,
                const std::string& description,
                size_t nbCols,
                size_t nbLines);

  /**
   * \brief Move the selection cursor
   * \param direction Where to fetch another selected item
   * \note Handles Inventory selection
   */
  void moveSelection(const e_direction direction);


private:
  std::vector<std::unique_ptr<ItemsContainer>> _stored; ///< Stored items

  size_t _selectedContainer; ///< Index of the currently selected container

  /// \todo dynamic first container place (based on biggest equipped items)
  /// Where to draw the current container
  graphics::Pos2 _currentContainerPosition = {0, 50};

  size_t _nbColumns; ///< Number of columns in the inventory
  size_t _nbLines;   ///< Number of lines in the inventory
};


#endif /* INVENTORY_HH_ */
