/*
 * EntriesMenu.hh
 *
 *  Created on: Jul 24, 2013
 *      Author: Zermingore
 */

#ifndef ENTRIESMENU_HH_
# define ENTRIESMENU_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/MenuEntry.hh>
# include <game/PathFinding.hh>


class EntriesMenu
{
public:
  /** \brief default Ctor
   */
  EntriesMenu();

  /** \brief virtual Dtor
   */
  virtual ~EntriesMenu();

  /** \brief X (column) coordinate getter
   */
  unsigned int getX();
  /** \brief Y (line) coordinate getter
   */
  unsigned int getY();

  /** \brief X (column) coordinate setter
   */
  void setX(unsigned int x);
  /** \brief Y (line) coordinate setter
   */
  void setY(unsigned int y);

  /** \brief PathFinding setter
   */
  void setPath(PathFinding *path);


  // TODO: merge and use a single function for all (4) directions
  /** \brief increments _selectedEntry modulo _nbEntries
   **  allowing cycling
   */
  void incrementSelectedEntry();
  /** \brief decrements _selectedEntry modulo _nbEntries
   **  allowing cycling
   */
  void decrementSelectedEntry();

  /** \brief draws the menu
   ** with its entries and the current entry highlighter
   */
  void draw();

  /** \brief builds the selection menu, filling _entries
   */
  virtual void build() = 0;

  /** \brief executes action matching _selectedEntry
   */
  virtual void executeEntry() = 0;


protected:
  /** \brief initializes the menu
   ** called by this->build()
   */
  void init();

  // the first entry, at the bottom, has the index 0
  unsigned int _selectedEntry; ///< Current selected entry
  unsigned int _nbEntries; ///< Total number of entries in the menu
  std::vector<MenuEntry> _entries; ///< Entries list
  sf::Vector2f _origin; ///< Origin position of the menu
  Image *_imageSelection; ///< Background image (entry)
  PathFinding *_path; ///< path (from Event)

private:
  /** \brief sets origin menu to the right cursor relative position
   */
  void setOrigin(); // TODO sets the menu at optimal position
};

#endif /* !ENTRIESMENU_HH_ */
