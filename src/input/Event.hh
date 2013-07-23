#ifndef EVENT_HH_
# define EVENT_HH_

# include <input/KeyManager.hh>
# include <graphics/GraphicEngine.hh>
# include <interface/SelectionMenu.hh>
# include <game/PathFinding.hh>


/** \brief Event processing class
 */

class Event
{
public:
  /** \brief Default Constructor
   **   processes input events
   */
  Event(KeyManager* km, GraphicEngine* ge);

  /** \brief Destructor
   */
  ~Event();

  /** \brief check if a generic event (like closing the window) occurs
   **   calls matching functions if any
   */
  void process();


private:
  /** Processes events relative to panel requests (show, save game, ...)
   */
  void panel();

  /** \brief Processes events while we're in a menu
   **   (for example arrows do not move game cursor but menu cursor)
   */
  void menu();

  /** \brief Processes events while moving a unit
   */
  void moveUnit();


  /** \brief Processes all game events
   */
  void game();

  /** \brief Looks for any released key.
   **   Reset the key timer matching the released key (if any)
   **   Reset switches if needed
   */
  void releasedKeys();

  sf::Event _event; ///< Event Manager
  KeyManager *_km; ///< KeyManager instance
  GraphicEngine *_ge; ///< GraphicEngine instance
  SelectionMenu *_selectionMenu; ///< in-game selection menu
  PathFinding *_path; ///< PathFinding
};

#endif /* !EVENT_HH_ */
