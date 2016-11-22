/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef MENU_HH_
# define MENU_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/menus/MenuEntry.hh>
# include <interface/InterfaceElement.hh>

enum class e_state;


namespace interface {


/**
 * \class Menu
 * \brief Generic Menu.
 * mother of \class InGameMenu
 */
class Menu: public InterfaceElement
{
public:
  /// \brief Constructor.
  Menu();

  /**
   * \brief allows to build a menu which entries are \param entries
   *   sets _origin according to current Cursor position
   *   and _selectedEntry to 0
   */
  explicit Menu(std::vector<std::shared_ptr<MenuEntry>> &entries);

  /// \todo: merge and use a single function for all (4) directions
  /**
   * \brief increments _selectedEntry modulo number of Entries
   *  allowing cycling
   */
  void incrementSelectedEntry() { ++_selectedEntry %= _entries.size(); }

  /**
   * \brief decrements _selectedEntry modulo _nbEntries
   *  allowing cycling
   */
  void decrementSelectedEntry();

  /**
   * \brief sets origin menu to the right cursor relative position
   */
  virtual void setOrigin(Coords origin);  /// \todo sets the menu at optimal position

  /**
   * \brief draws the menu
   * with its entries and the current entry highlighter
   */
  void draw();

  /**
   * \brief sets _selectedEntry to 0
   */
  void resetSelectedEntry() { _selectedEntry = 0; }

  /**
   * \brief builds the selection menu, filling _entries
   * \param state The state we're about to push
   */
  virtual void build(/* e_state state */) = 0;


  // Selection motion
  virtual void moveUp()    {}
  virtual void moveDown()  {}
  virtual void moveLeft()  {}
  virtual void moveRight() {}

  /**
   * \brief executes action matching _selectedEntry
   */
  virtual void executeEntry();

  /**
   * \brief Removes the entries of the menu
   */
  virtual void clear() { _entries.clear(); }

  /**
   * \brief Callback for closing the menu
   */
  virtual void close() = 0;

  virtual void validate() = 0;


protected:
  /**
   * \brief list of entries getter
   * \return a pointer over _entries array
   * \note this function is used to retrieve
   *   informations from menu stack (see \class Status)
   */
  auto getEntries() const { return _entries; }

  /**
   * \brief selected entry getter
   * \return current selected entry
   * \note this function is used to retrieve
   *   informations from menu stack (see \class Status)
   */
  unsigned int selectedEntry() { return _selectedEntry; }


  std::vector<std::shared_ptr<MenuEntry>> _entries; ///< Entries list
  Coords _origin; ///< menu origin

  unsigned int _selectedEntry; ///< Current selected entry
                               ///< the first entry, is at the bottom,
                               ///< it has the index 0

  graphics::Image _imageSelection; ///< Emphasis of the selected entry
};


} // namespace interface

#endif /* !MENU_HH_ */
