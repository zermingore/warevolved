/**
 * \file
 * \date December 11, 2020
 * \author Zermingore
 * \brief ItemContainer class declaration and e_container_type enum definition
 */


#ifndef ITEMS_CONTAINER_HH_
# define ITEMS_CONTAINER_HH_

# include <memory>
# include <string>
# include <vector>

# include <interface/InterfaceElement.hh>


namespace resources {
  class Text;
}

class Item;
enum class e_direction;


/**
 * \enum e_container_type
 * \brief Items container type (inventory)
 */
enum class e_container_type
{
  EQUIPPED, ///< Unit type agnostic
  BACKPACK, ///< Soldier only
  POCKET,   ///< Soldier only
  TRUNK,    ///< Vehicle only
  CELL,     ///< Cell's Inventory specific case
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
                 int nbCols,
                 int nbLines);


  ///< _selected getter
  /// \todo rename getter or attribute?
  auto selectedItemCoords() const { return _selected; }

  ///< type getter
  auto type() { return _type; }

  /**
   * \brief Check if the currently selected Item is usable
   * \return true if the currently selected Item is usable; false otherwise
  */
  bool selectedItemUsable();

  /**
   * \brief Check if the currently selected Item is equippable
   * \return true if the currently selected Item is equippable; false otherwise
   */
  bool selectedItemEquippable();

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

  /**
   * \brief Use the currently selected Item
   */
  void useItem();

  /**
   * \brief Drop the currently selected Item
   */
  void dropItem();

  /**
   * \brief Check wether the container is empty
   * \return true if empty; false otherwise
   */
  bool empty();


private:
  e_container_type _type;  ///< Type of the container
  std::string _name;       ///< Displayed name
  bool _unlimited = false; ///< Unlimited container size (equipped / Cell)

  /// Items in the container and their coordinates in the container
  std::vector<std::pair<Coords, std::unique_ptr<Item>>> _stored;

  size_t _nbColumns; ///< Number of columns (x coordinate)
  size_t _nbLines;   ///< Number of lines (y coordinate)

  std::vector<bool> _freeCells; ///< Keeping track of free space

  Coords _selected; ///< Selected item location

  std::shared_ptr<resources::Text> _label; ///< button label text
  std::shared_ptr<resources::Text> _labelDescription; ///< description text
};

#endif /* ITEMS_CONTAINER_HH_ */
