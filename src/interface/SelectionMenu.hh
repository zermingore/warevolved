#ifndef SELECTIONMENU_HH_
# define SELECTIONMENU_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/MenuEntry.hh>


/** \brief in-game SelectionMenu class
 */

class SelectionMenu
{
public:
  /** \brief Default Constructor
   ** initializes buttons background image (sprite size)
   */
  SelectionMenu();

  /** \brief Destructor
   */
  ~SelectionMenu();

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


  // TODO: merge and use a single function for all (4) directions
  /** \brief increments _selectedEntry modulo _nbEntries
   **  allowing cycling
   */
  void incrementSelectedEntry();
  /** \brief decrements _selectedEntry modulo _nbEntries
   **  allowing cycling
   */
  void decrementSelectedEntry();

  /** \brief builds the selection menu, filling _entries
   */
  void build();

  /** \brief draws the menu
   ** with its entries and the current entry highlighter
   */
  void draw();

  /** \brief executes action matching _selectedEntry
   */
  void executeEntry();


private:
  unsigned int _x; ///< SelectionMenu related selected cell x (column) position
  unsigned int _y; ///< SelectionMenu related selected cell y (line) position

  unsigned int _selectedEntry; ///< Current selected entry
  // the first entry, at the bottom, has the index 0
  unsigned int _nbEntries; ///< Total number of entries in the menu
  std::vector<MenuEntry> _entries; ///< Entries list
  sf::Vector2f _origin; ///< Origin position of the menu

  Image *_imageSelection; ///< Background image (entry)
};

#endif /* !SELECTIONMENU_HH_ */
