/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 * \namespace interface
 * \brief Interface generic Menu class declaration
 */

#ifndef MENU_HH_
# define MENU_HH_

# include <cstddef>
# include <memory>
# include <vector>

# include <interface/menus/MenuEntry.hh>
# include <interface/InterfaceElement.hh>


enum class e_state;

namespace graphics {
  class Sprite;
}

namespace interface {
  class MenuEntry;
}



namespace interface {


/**
 * \class Menu
 * \brief Generic Menu (abstract class)
 * \note Mother of InGameMenu class
 */
class Menu: public InterfaceElement
{
public:
  /**
   * \brief Default constructor. Initializes the graphic attributes
   */
  Menu();

  /**
   * \brief increments _selectedEntry modulo number of Entries
   * \note Allow cycling
   */
  void incrementSelectedEntry() { ++_selectedEntry %= _entries.size(); }

  /**
   * \brief decrements _selectedEntry modulo _nbEntries
   *   allowing cycling
   */
  void decrementSelectedEntry();

  /**
   * \brief sets origin menu to the right cursor relative position
   * \todo set the menu at optimal position
   */
  virtual void setOrigin(const Coords origin);

  /**
   * \brief draws the menu its entries and the current entry highlighter
   */
  void draw() override;

  /**
   * \brief sets _selectedEntry to 0
   */
  void resetSelectedEntry() { _selectedEntry = 0; }

  /**
   * \brief builds the selection menu, filling _entries
   */
  virtual void build() = 0;


  /**
   * \brief Move the selection cursor up
   */
  virtual void moveUp()    {}
  /**
   * \brief Move the selection cursor down
   */
  virtual void moveDown()  {}
  /**
   * \brief Move the selection cursor to the left
   */
  virtual void moveLeft()  {}
  /**
   * \brief Move the selection cursor to the right
   */
  virtual void moveRight() {}


  /**
   * \brief Removes the entries of the menu
   */
  virtual void clear() { _entries.clear(); }

  /**
   * \brief executes action matching _selectedEntry
   */
  virtual void validate() = 0;

  /**
   * \brief Resume the current menu
   *   as a default behavior, updates the cursor coordinates to the menu ones
   */
  virtual void resume();

  /**
   * \brief list of entries getter
   * \return a pointer over _entries array
   * \note this function is used to retrieve
   *   informations from menu stack (see Status class)
   */
  auto getEntries() const { return _entries; }

  /**
   * \brief selected entry getter
   * \return current selected entry
   * \note this function is used to retrieve
   *   informations from menu stack (see Status class)
   */
  size_t selectedEntry() { return _selectedEntry; }


protected:
  std::vector<std::shared_ptr<MenuEntry>> _entries; ///< Entries list
  Coords _origin; ///< menu origin

  /// Current selected entry (the first entry [index 0], is at the bottom)
  size_t _selectedEntry;

  /// Emphasis of the selected entry
  std::shared_ptr<graphics::Sprite> _imageSelection;
};


} // namespace interface

#endif /* !MENU_HH_ */
