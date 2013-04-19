#ifndef EVENT_HH_
# define EVENT_HH_

# include <input/KeyManager.hh>
# include <graphics/GraphicEngine.hh>
# include <common/Status.hh>

/** \brief Event processing class
 */

class Event
{
public:
  /** \brief Default Constructor
   */
  Event();
  Event(sf::RenderWindow* window,
		KeyManager* km,
		GraphicEngine* ge,
		Status* status);

  /** \brief Destructor
   */
  ~Event();

  /** \brief check if a generic event (like closing the window) occurs
   **   calls matching functions if any
   */
  void process();


private:
  /** \brief process all game events
   */
  void game();

  /** \brief reset the key timer matching the released key
   */
  void resetTimer();

  sf::RenderWindow* _window; ///< main rendering window
  sf::Event _event; ///< Event Manager
  KeyManager* _km; ///< KeyManager instance
  GraphicEngine* _ge; ///< GraphicEngine instance
  Status* _status; ///< global game Status
};

#endif /* !EVENT_HH_ */
