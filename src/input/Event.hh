#ifndef EVENT_HH_
# define EVENT_HH_

# include <input/KeyManager.hh>
# include <graphics/GraphicsEngine.hh>
# include <interface/menus/Menu.hh>
# include <game/PathFinding.hh>
# include <interface/menus/InGameMenu.hh>


/** \class processing class
 */
class Event
{
public:
  /** \brief Constructor
   **   processes input events
   */
  Event(std::shared_ptr<KeyManager> km, std::shared_ptr<GraphicsEngine> ge);

  /** \brief check if a generic event (like closing the window) occurs
   **   calls matching functions if any
   ** \return false if a quit request has been sent
   **   true otherwise
   */
  bool process();


private:
  /** \brief Processes events relative to right panel requests
   **   (show, save game, ...)
   ** and Menu bar
   */
  void panels();

  /** \brief Processes events while we're in the selection menu
   **   (for example arrows do not move game cursor but menu cursor)
   ** \param menu menu of which we want to manage events
   */
  void selectionMenu();

  /** \brief select a cell
   **   browse Cells containing an available target on keyboard strikes
   */
  void selectTarget();

  /** \brief Processes events while moving a unit
   */
  void moveUnit();

  /** \brief Processes all game events
   ** called when we're not browsing a menu, moving a unit, ...
   ** \return false if we got an exit request true otherwise
   */
  bool game();

  /** \brief Looks for any released key.
   **   Reset the key timer matching the released key (if any)
   **   Reset switches if needed
   */
  void releasedKeys();

  sf::Event _event; ///< Event Manager
  std::shared_ptr<KeyManager> _km; ///< KeyManager instance
  std::shared_ptr<GraphicsEngine> _ge; ///< GraphicsEngine instance
  std::shared_ptr<InGameMenu> _inGameMenu; ///< in-game action menu
  std::shared_ptr<PathFinding> _path; ///< PathFinding path
};

#endif /* !EVENT_HH_ */
