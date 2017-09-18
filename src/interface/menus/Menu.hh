/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef MENU_HH_
# define MENU_HH_

# include <memory>
# include <vector>

# include <resources/Sprite.hh>
# include <interface/menus/MenuEntry.hh>
# include <interface/InterfaceElement.hh>

enum class e_state;


namespace interface {


/**
 * \class Menu
 * \brief Generic Menu (abstract class)
 * mother of \class InGameMenu
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
   * \param state The state we're about to push
   */
  virtual void build() = 0;


  // Selection motion
  virtual void moveUp()    {}
  virtual void moveDown()  {}
  virtual void moveLeft()  {}
  virtual void moveRight() {}


  /**
   * \brief Removes the entries of the menu
   */
  virtual void clear() { _entries.clear(); }

  /**
   * \brief Callback for closing the menu
   */
  virtual void close() = 0;

  /**
   * \brief executes action matching _selectedEntry
   */
  virtual void validate() = 0;

  /**
   * \brief Resume the current menu
   *   as a default behavior, updates the cursor coordinates to the menu ones
   */
  virtual void resume();



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
  size_t selectedEntry() { return _selectedEntry; }



  std::vector<std::shared_ptr<MenuEntry>> _entries; ///< Entries list
  Coords _origin; ///< menu origin

  size_t _selectedEntry; ///< Current selected entry
                               ///< the first entry, is at the bottom,
                               ///< it has the index 0

  ///< Emphasis of the selected entry
  std::shared_ptr<resources::Sprite> _imageSelection;
};


} // namespace interface

#endif /* !MENU_HH_ */
