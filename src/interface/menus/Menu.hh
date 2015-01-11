/*
 * interface/menus/Menu.hh
 *
 *  Created on: July 24, 2013
 *      Author: Zermingore
 */

#ifndef MENU_HH_
# define MENU_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/InterfaceBlock.hh>
# include <interface/menus/MenuEntry.hh>
# include <game/PathFinding.hh>
# include <common/enums/modes.hh>


/** \class Menu: generic Menu class
 ** mother of \class InGameMenu
 */
class Menu: public InterfaceBlock
{
public:
  /** \brief default Ctor
   */
  Menu();

  /** \brief allows to build a menu which entries are \param entries
   **   sets _origin according to current Cursor position
   **   and _selectedEntry to 0
   */
  explicit Menu(std::vector<MenuEntry> &entries);

  // TODO: merge and use a single function for all (4) directions
  /** \brief increments _selectedEntry modulo number of Entries
   **  allowing cycling
   */
  inline void incrementSelectedEntry() { ++_selectedEntry %= _entries.size(); }

  /** \brief decrements _selectedEntry modulo _nbEntries
   **  allowing cycling
   */
  void decrementSelectedEntry();

  /** \brief sets origin menu to the right cursor relative position
   */
  void setOrigin(); // TODO sets the menu at optimal position

  /** \brief draws the menu
   ** with its entries and the current entry highlighter
   */
  void draw();

  /** \brief sets _selectedEntry to 0
   */
  inline void resetSelectedEntry() { _selectedEntry = 0; }

  /** \brief builds the selection menu, filling _entries
   ** \param mode The mode we're about to push
   */
  virtual void build(e_mode mode) = 0;

  /** \brief executes action matching _selectedEntry
   */
  virtual void executeEntry() = 0;

  /** \brief loads a previously saved menu
   ** \param menu menu to load
   */
  void loadMenu();


protected:
  /** \brief initializes the menu
   ** called by this->build()
   */
  void init();

  /** \brief list of entries getter
   ** \return a pointer over _entries array
   ** \note this function is used to retrieve
   **   informations from menu stack (see \class Status)
   */
  // inline const std::vector<std::shared_ptr<MenuEntry>> &getEntries() const
  // { return *_entries; }

  inline std::vector<MenuEntry> getEntries() const
  { return _entries; }

  /** \brief selected entry getter
   ** \return current selected entry
   ** \note this function is used to retrieve
   **   informations from menu stack (see \class Status)
   */
  inline unsigned int selectedEntry() { return _selectedEntry; }

  unsigned int _selectedEntry; ///< Current selected entry
                               ///< the first entry, is at the bottom,
                               ///< it has the index 0

  std::vector<MenuEntry> _entries; ///< Entries list
  Image _imageSelection; ///< Background image (entry)
};

#endif /* !MENU_HH_ */
