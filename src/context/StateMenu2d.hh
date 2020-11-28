/**
 * \file
 * \date November 25, 2020
 * \author Zermingore
 * \brief StateMenu2d class declaration
 */

#ifndef STATE_MENU_2D_HH_
# define STATE_MENU_2D_HH_

# include <memory>
# include <functional>

# include <context/State.hh>

enum class e_state;

namespace interface {
  class InGameMenu;
}



/**
 * \class StateMenu2d
 * \brief The State which applies to any menu tree
 */
class StateMenu2d: public State
{
public:
  /**
   * \brief Default constuctor
   */
  explicit StateMenu2d(
    std::initializer_list<std::unique_ptr<interface::InGameMenu>> args);

  /**
   * \brief default destructor
   */
  ~StateMenu2d() override = default;


  /**
   * \brief Save the menu coordinates.
   * \todo suspend() should also save selected entry.
   */
  void suspend() override final;

  /**
   * \brief re-build the menu.
   */
  void resume() override final;

  /**
   * \brief Draws the menus
   */
  void draw() override final;

  /**
   * \brief Closes the menu: Pop the current state
   */
  void cancel();

  /**
   * \brief Fetch the attribute from the list
   * \note Expects one attribute per menu: its coordinates
   * \note Aborts if no attribute was found
   */
  void fetchAttributes() override final;

  /**
   * \brief Cancel callback setter
   * \param callback Callback called when the menu is fully canceled
   */
  void setCancelCallback(const std::function<void()> callback) {
    _cancelCallback = callback;
  }

  /**
   * \brief Confirm callback setter
   * \param callback Callback called when the menu is fully closed (confirmed)
   */
  void setConfirmCallback(const std::function<void()> callback) {
    _confirmCallback = callback;
  }


private:
  /**
   * \brief Highlights the entry on top of the current one
   * \note loops on the last entry if called on the first one
   */
  void moveUp();

  /**
   * \brief Highlights the entry bellow the current one
   * \note loops on the first entry if called on the last entry
   */
  void moveDown();

  /**
   * \brief Highlights the entry on the left of the current one
   * \note Only applicable for crew member entry
   */
  void moveLeft();

  /**
   * \brief Highlights the entry on the right of the current one
   * \note Only applicable for crew member entry
   */
  void moveRight();

  /**
   * \brief Validates the current entry selected
   */
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();

  /**
   * \brief Give the focus to the next menu (to the right)
   */
  void setFocusNextMenu();


  /// 'main' menu + Sub-menus
  std::vector<std::unique_ptr<interface::InGameMenu>> _menus;
  std::vector<Coords> _coords; ///< Menus coordinates

  int _currentMenu = 0;  ///< Which menu is currently browsed
  int _selectionIdx = 0; ///< Currently selected entry index

  bool _confirmActive; ///< 'confirm' entry available?

  std::function<void()> _cancelCallback; ///< Callback on menu cancelation
  std::function<void()> _confirmCallback; ///< Callback on menu confirmation
};

#endif /* !STATE_MENU_2D_HH_  */
