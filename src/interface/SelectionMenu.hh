#ifndef SELECTIONMENU_HH_
# define SELECTIONMENU_HH_

# include <common/include.hh>
# include <common/Status.hh>
# include <resources/Image.hh>


/** \ brief in-game SelectionMenu class
 ** Manages cursor shape, animation
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

  sf::Sprite getSprite();

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


private:
  // map attributes
  // unsigned int _nbColumns;
  // unsigned int _nbLines;

  // SelectionMenu specific
  unsigned int _x; ///< SelectionMenu x (column) position
  unsigned int _y; ///< SelectionMenu y (line) position

  unsigned short _selectedEntry; ///< Current selected entry
  unsigned short _nbEntries; ///< total number of entries in the menu

  sf::Vector2f _origin; ///< Origin position of the menu

  Image* _imageBackground; ///< background image (entry)
  sf::Sprite *_sprite;
  sf::Texture *_texture;
};

#endif /* !SELECTIONMENU_HH_ */
