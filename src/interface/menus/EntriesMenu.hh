/*
 * interface/menus/EntriesMenu.hh
 *
 *  Created on: July 24, 2013
 *      Author: Zermingore
 */

#ifndef ENTRIESMENU_HH_
# define ENTRIESMENU_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/menus/MenuEntry.hh>
# include <game/PathFinding.hh>
# include <common/enums/modes.hh>


/**
   * \brief EntriesMenu: generic Menu class
 * mother of \class InGameMenu
 */
class EntriesMenu
{
public:
  /**
   * \brief default Ctor
   */
  EntriesMenu();

  /**
   * \brief allows to build a menu which entries are \param entries
   *   sets _origin according to current Cursor position
   *   and _selectedEntry to 0
   */
  explicit EntriesMenu(std::vector<MenuEntry> entries);

  /// \brief virtual Destructor
  virtual ~EntriesMenu();

   /// \todo: merge and use a single function for all (4) directions
  /**
   * \brief increments _selectedEntry modulo _nbEntries
   *  allowing cycling
   */
  void incrementSelectedEntry();
  /**
   * \brief decrements _selectedEntry modulo _nbEntries
   *  allowing cycling
   */
  void decrementSelectedEntry();

  /**
   * \brief draws the menu
   * with its entries and the current entry highlighter
   */
  void draw();

  /**
   * \brief sets _selectedEntry to 0
   */
  void resetSelectedEntry();

  /**
   * \brief builds the selection menu, filling _entries
   * \param mode The mode we're about to push
   */
  virtual void build(e_mode mode) = 0;

  /**
   * \brief executes action matching _selectedEntry
   */
  virtual void executeEntry() = 0;

  /**
   * \brief loads a previously saved menu
   * \param menu menu to load
   */
  void loadMenu(EntriesMenu *menu);


protected:
  /**
   * \brief initializes the menu
   * called by this->build()
   */
  void init();

  /**
   * \brief list of entries getter
   * \return a pointer over _entries array
   * \note this function is used to retrieve
   *   informations from menu stack (see \class Status)
   */
  std::vector<MenuEntry> *getEntries();

  /**
   * \brief selected entry getter
   * \return current selected entry
   * \note this function is used to retrieve
   *   informations from menu stack (see \class Status)
   */
  unsigned int selectedEntry();

  /**
   * \brief sets origin menu to the right cursor relative position
   */
  void setOrigin();  /// \todo sets the menu at optimal position


  unsigned int _selectedEntry; ///< Current selected entry
                               ///< the first entry, is at the bottom,
                               ///< it has the index 0
  unsigned int _nbEntries; ///< Total number of entries in the menu
  std::vector<MenuEntry> *_entries; ///< Entries list
  sf::Vector2f _origin; ///< Origin position of the menu
  Image _imageSelection; ///< Background image (entry)
};

#endif /* !ENTRIESMENU_HH_ */
