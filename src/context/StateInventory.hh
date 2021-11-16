/**
 * \file
 * \date December 6, 2020
 * \author Zermingore
 * \brief StateInventory class declaration
 */

#ifndef STATE_INVENTORY_HH_
# define STATE_INVENTORY_HH_

# include <memory>
# include <vector>
# include <context/State.hh>

class Inventory;



/**
 * \class StateInventory
 * \brief State active while browsing an inventory
 */
class StateInventory: public State
{
public:
  /**
   * \brief Registers to callbacks. Initializes the graphical attributes
   */
  StateInventory();

  /**
   * \brief Default destructor
   */
  ~StateInventory() override = default;


  /**
   * \brief Fetch the attribute from the list
   * \note Expects one attribute: Inventories vector
   * \note Aborts if no attribute was found
   * \note Aborts if less than two Inventories were forwarded
   * \note Expects at least:
   *   - The selected Unit Inventory
   *   - The current Cell Inventory
   */
  void fetchAttributes() override final;

  /**
   * \brief Exits the current State
   */
  void exit();

  /**
   * \brief Draw the inventory
   */
  virtual void draw() override final;

  /**
   * \brief Fetch Inventories
   * \see fetchAttributes()
   */
  void resume() override final;


private:
  /// Move the cursor up
  void selectUp();

  /// Move the cursor down
  void selectDown();

  /// Move the cursor left
  void selectLeft();

  /// Move the cursor right
  void selectRight();


  /// \todo Use _cursorCoords; make them selected inventory dependent
  Coords _cursorCoords;         ///< Selected Inventory cursor position
  size_t _currentInventory = 0; ///< Currently selected Inventory

  /// List of relevant Inventories, containing:
  /// at least:
  /// - The selected Unit Inventory
  /// - The currently hovered Cell Inventory
  /// Eventually:
  /// - The adjacent allies Inventories
  std::vector<std::shared_ptr<Inventory>> _inventories;
};


#endif /* !STATE_INVENTORY_HH_ */
