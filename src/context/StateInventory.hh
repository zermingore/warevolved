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
   * \brief registers to callbacks. Initializes the graphical attributes
   */
  StateInventory();

  /**
   * \brief Resets the unit's sprite
   * \note It is necessary if the move was canceled
   */
  ~StateInventory() override = default;


  /**
   * \brief Fetch the attribute from the list
   * \note Expects one attribute: the relevant Inventory
   * \note Aborts if no attribute was found
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
   * \brief \todo Fetch Inventory
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
  Coords _cursorCoords; ///< Inventory cursor position

  std::vector<std::shared_ptr<Inventory>> _inventories;
  size_t _currentInventory = 0;
};


#endif /* !STATE_INVENTORY_HH_ */
