#ifndef EVENT_HH_
# define EVENT_HH_

# include <memory>
# include <SFML/Window.hpp>


class KeyManager;

/** \class processing class
 */
class Event
{
public:
  /** \brief Constructor
   **   processes input events
   */
  Event(std::shared_ptr<KeyManager> km);

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
};

#endif /* !EVENT_HH_ */
