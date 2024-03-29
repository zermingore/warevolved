/**
 * \file
 * \date December 11, 2020
 * \author Zermingore
 * \brief Inventory class declaration
 */

#ifndef INVENTORY_HH_
# define INVENTORY_HH_

# include <cstddef>
# include <memory>
# include <string>
# include <vector>
# include <optional>
# include <functional>

# include <graphics/graphic_types.hh>
# include <game/Item.hh>
# include <game/ItemsContainer.hh>


enum class e_directions;



/**
 * \class Inventory
 * \brief Possesions of an entity (Unit, Building, Vehicle, ...)
 */
class Inventory
{
public:
  /**
   * \brief Default constructor. Initializes the equipped items container
   * \todo Destructor? Move every Item to the Cell Inventory?
   */
  Inventory();


  /**
   * \brief _containers getter
   * \return Items containers
   */
  auto containers() { return _containers; }


  /**
   * \brief Draw the components of the Inventory (equipped list and containers)
   * \param direction Direction offset where to draw the Inventory
   */
  void draw(e_direction direction);

  /**
   * \brief Draw the Inventory in the side Panel
   * \param coords Panel coordinates
   */
  void drawInPanel(const graphics::Pos2& coords);

  /**
   * \brief Create and add a container to the Inventory
   * \param type Type of the container
   * \param name Displayed container name
   * \param nbCols Number of inventory cells (column)
   * \param nbLines Number of inventory cells (lines)
   * \note Unlimited container size if nbCols or nbLines <= 0
   */
  void addContainer(e_container_type type,
                    const std::string& name,
                    int nbCols,
                    int nbLines);

  /**
   * \brief Add a new item in the equipped list
   * \param name Displayed Item name
   * \param description New Item description
   * \param nbCols New Item number of used columns
   * \param nbLines New Item number of used lines
   * \param slot Item category
   * \param range Item effective min, max range
   * \param onUseValue Item usage effect value (damage, heal)
   * \param use Callback function triggered on Item usage
   * \return true on success; false on impossible add (item too large)
   * \note Creating a new Items from these parameters
   * \todo only one parameter to take and forward: item type
   */
  bool addEquip(const std::string& name,
                const std::string& description,
                size_t nbCols,
                size_t nbLines,
                e_item_slot slot,
                Range range,
                size_t onUseValue,
                const std::function<void()>& use = {});

  /**
   * \brief Move the given Item to the equip list
   * \param item Item to equip
   * \return true on success; false on impossible add (item too large)
   */
  bool addEquip(std::unique_ptr<Item> item);

  /**
   * \brief Move the selection cursor
   * \param direction Where to fetch another selected item
   * \note Handles Inventory selection
   */
  void moveSelection(const e_direction direction);

  /**
   * \brief Use the currently selected Item
   */
  void useItem();

  /**
   * \brief Drop the currently selected Item
   * \note The Item will belong to the Cell's Inventory
   */
  void dropItem();

  /**
   * \brief Take an Item on the current Cell
   * \note The Item will belong to the selected Unit's Inventory
   */
  void takeItem();

  /**
   * \brief Check wether the Containers (if any) are all empty
   * \return true if no item is found in the inventory; false otherwise
   */
  bool empty();

  /**
   * \brief Check wether the selected Container (if any) is empty
   * \return true if no item is found in the selected container; false otherwise
   */
  bool emptySelection();

  /**
   * \brief Check if the currently selected item is usable
   * \return true if the Item is usable, false otherwise
   */
  bool usableSelectedItem();

  /**
   * \brief Check wether the current Item is equipped
   * \return true if equipped; false otherwise
   * \note The returned flag is based on the Item Container type
   */
  bool equippedItem();

  /**
   * \brief Check if the currently selected Item can be equipped
   * \return true if the current Item can be equipped; false otherwise
   */
  bool selectedItemEquippable();

  /**
   * \brief Equip the currently selected Item
   * \todo Unequip incompatible items (one main weapon, ...)
   */
  void equip();

  /**
   * \brief Unquip the currently selected Item
   * \return true on success, false otherwise (no more space in containers)
   */
  bool unequip();

  /**
   * \brief Get the Unit's attack value (in case it's attacking, not defending)
   * \return Attack value based on relevant equipped weapon
   */
  size_t attackValue() const;

  /**
   * \brief Get the Unit's counter attack value (in case it's defending only)
   * \return Attack value based on secondary weapon (if equipped and usable)
   */
  size_t counterAttackValue() const;

  /**
   * \brief Return the (min, max) range of the equipped weapon
   * \return A map of item_slot and pair of (if availables) min, max values
   * \note Returns example: ranges[SECONDARY_WEAPON] = <std::nullopt, 1>
   */
  std::map<e_item_slot, Range> range() const;


private:
  std::vector<std::shared_ptr<ItemsContainer>> _containers; ///< Stored items

  size_t _selectedContainer; ///< Index of the currently selected container

  /// \todo dynamic first container place (based on biggest equipped items)
  /// Position in Pixels where to draw the current container
  graphics::Pos2 _currentContainerPosition = {0, 50};
};


#endif /* INVENTORY_HH_ */
