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
# include <optional>

# include <interface/InterfaceElement.hh>


namespace resources {
  class Text;
}

class Item;
enum class e_direction;
enum class e_item_slot;


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
  auto selectedItemCoords() const { return _selectedItemCoords; }

  ///< _type getter
  auto type() { return _type; }

  /**
   * \brief Get the Container size
   * \return Container size as a Coords (_nbColumns, _nbLines)
   */
  Coords size() const { return {_nbColumns, _nbLines}; }

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

  /**
   * \brief Add the given Item to the container
   * \param item Item to add
   * \param dst Where to add the Item in the inventory
   */
  void add(std::unique_ptr<Item> item, const Coords& dst);

  /**
   * \brief Check if an Item fits in a container, depending on its size
   * \param itemSize Item size
   * \return Coordinates where the Item would fit if any
   * \todo Try to rotate the Item if it does not fit
   */
  std::optional<Coords> addable(Coords itemSize);

  /**
   * \brief Select the next item, according to the given direction
   * \return Direction where another ItemContainer should be considered
   *   Used when "trying" to cross inventory borders (ex: left from most-left)
   *   return e_direction::NONE if a new selection can be made in this container
   */
  e_direction selectItem(const e_direction direction);

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

  /**
   * \brief Clear the cursor selection drawing
   * \param value true if the selection cursor should be drawn; false otherwise
   */
  void setDrawSelectionCursor(bool value) { _drawSelectionCursor = value; }

  /**
   * \brief Reset the selected Item (coordinates)
   * \note Select the top-left Item
   */
  void resetSelectedItem();

  /**
   * \brief Return the currenlty equipped Item
   * \return Item (give ownership)
   */
  std::unique_ptr<Item> item();

  /**
   * \brief Re-organize Items in the Container, avoiding gaps
   * \warning Handling only unlimited ItemsContainers
   */
  void reorganizeItems();

  /**
   * \brief Return the relevant weapon attack value
   * \return Attack value of the relevant equipped weapon
   *    in the following order: the main weapon, secondary weapon, 0
   * \todo Do this in the Inventory and make ItemsContainer iterable
   * \todo Check if the weapons are usable
   */
  size_t attackValue() const;

  /**
   * \brief Return the counter attack value (based on secondary weapon)
   * \return Secondary weapon damage value if usable, 0 otherwise
   * \todo If secondary weapon usable
   */
  size_t counterAttackValue() const;

  /**
   * \brief Get the maximal effective range for every stored Item type
   * \return (min, max) range for every Item type
   * \note Returns for instance: ranges[MAIN_WEAPON] = (3, std::nullopt)
   */
  std::map<e_item_slot, Range> range() const;


private:
  e_container_type _type;  ///< Type of the container
  std::string _name;       ///< Displayed name
  bool _unlimited = false; ///< Unlimited container size (equipped / Cell)

  /// Items in the container and their coordinates in the container
  std::vector<std::pair<Coords, std::unique_ptr<Item>>> _stored;

  size_t _nbColumns; ///< Number of columns (x coordinate)
  size_t _nbLines;   ///< Number of lines (y coordinate)

  std::vector<bool> _freeCells; ///< Keeping track of free space

  Coords _selectedItemCoords; ///< Selected item location
  bool _drawSelectionCursor = false; ///< Show / hide selection cursor

  std::shared_ptr<resources::Text> _label; ///< button label text
  std::shared_ptr<resources::Text> _labelDescription; ///< description text
};

#endif /* ITEMS_CONTAINER_HH_ */
