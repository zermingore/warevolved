#ifndef PLAYER_HH_
# define PLAYER_HH_

/**
 * \file Player definition.
 * \date August 1, 2013
 * \author Zermingore
 */

# include <memory>
# include <interface/Interface.hh>

class Interface;


/**
 * \class Player
 * \brief A player can be controled by a human or an AI.
 */
class Player
{
public:
  /// deleted default constructor
  Player() = delete;

  /**
   * \brief Constructor. Sets the Player's index to a unique value.
   * \param c color used by the player
   */
  explicit Player(Color c);


  /**
   * \brief Player identifier getter.
   * \return Player's identifier.
   */
  size_t id() { return _id; }


  void moveCursorUp();
  void moveCursorDown();
  void moveCursorLeft();
  void moveCursorRight();

  /**
   * \brief Player's interface getter.
   * \return Interface pointer.
   */
  std::shared_ptr<interface::Interface> interface() { return _interface; }



private:
  // (logicaly const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player's identifier
  std::shared_ptr<interface::Interface> _interface; ///< User Interface
  std::shared_ptr<interface::Cursor> _cursor; ///< Map Cursor
};

#endif /* !PLAYER_HH_ */
