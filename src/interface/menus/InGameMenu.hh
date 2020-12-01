/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 * \namespace interface
 * \brief InGameMenu class declaration
 */

#ifndef IN_GAME_MENU_HH_
# define IN_GAME_MENU_HH_

# include <memory>
# include <mutex>
# include <functional>

# include <interface/menus/Menu.hh>

enum class e_state;

class Unit;

namespace interface {

/**
 * \class InGameMenu
 * \brief Refers to the menu called when
 *   A unit is picked
 *   A void cell is clicked
 */
class InGameMenu: public Menu
{
public:
  /**
   * \brief Builds the selection menu, filling the entries.
   */
  virtual void build() override = 0;

  /**
   * \brief Destructor. Lock before destroying the object
   */
  ~InGameMenu() override;


  /**
   * \brief Cursor motion: up
   */
  void moveUp() override final;

  /**
   * \brief Cursor motion: down
   */
  void moveDown() override final;

  /**
   * \brief Validate selected entry
   */
  void validate() override final;

  /**
   * \brief Get the currently highlighted entry
   * \return Highlighted entry type
   */
  e_entry currentSelection();

  /**
   * \brief updates the graphics attributes of the menu
   */
  void update() override final;

  /**
   * \brief Draw the entries of the menu
   */
  virtual void draw() override;

  /**
   * \brief Enable the "Confirm" entry of the menu, if any
   * \param confirmActive Confirm flag value
   */
  void setConfirmActive(bool confirmActive) {
    _confirmActive = confirmActive;
  }


protected:
  /**
   * \brief Default cancel entry callback (pops the menu)
   */
  virtual void cancel();

  /**
   * \brief Adds a cancel entry into the menu
   */
  void addCancelEntry(const std::function<void()>& cancel_callback);


  bool _confirmActive = false; ///< Should the menu show its "Confirm" entry?
  std::mutex _lock; /// Prevent from drawing a not anymore current State (crash)
};


} // namespace interface


#endif /* !IN_GAME_MENU_HH_ */
