/**
 * \file
 * \date December 6, 2020
 * \author Zermingore
 * \brief StateInventory class declaration
 */

#ifndef STATE_INVENTORY_HH_
# define STATE_INVENTORY_HH_

# include <memory>
# include <context/State.hh>



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


  Coords _cursorCoords; ///< Inventory cursor position
};


#endif /* !STATE_INVENTORY_HH_ */
