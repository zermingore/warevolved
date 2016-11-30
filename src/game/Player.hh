/**
 * \file Player definition.
 * \date August 1, 2013
 * \author Zermingore
 */


#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <memory>
# include <interface/Interface.hh>


namespace interface {
  class Interface;
  class Cursor;
  class InGameMenu;
}


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


  // Cursor motion
  void moveCursorUp();
  void moveCursorDown();
  void moveCursorLeft();
  void moveCursorRight();

  // Unit motion
  void moveUnitUp();
  void moveUnitDown();
  void moveUnitLeft();
  void moveUnitRight();
  void validateMoveUnit();


  // Cursor click
  void select();

  // Exit current mode (selection)
  void cancel();

  /**
   * \brief Player's interface getter.
   * \return Interface pointer.
   */
  std::shared_ptr<interface::Interface> interface() { return _interface; }

  /**
   * \brief Cursor getter.
   * \return a pointer to the player's cursor.
   */
  std::shared_ptr<interface::Cursor> cursor() { return _cursor; }

  /**
   * \brief InGameMenu getter.
   * \return a pointer to the in game menu.
   */
  std::shared_ptr<interface::InGameMenu> menu() { return _menu; }


  bool updateSelectedUnit();



private:
  // (logicaly const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player's identifier

  std::shared_ptr<interface::Interface>  _interface; ///< User Interface
  std::shared_ptr<interface::Cursor>     _cursor;    ///< Map Cursor
  std::shared_ptr<interface::InGameMenu> _menu;      ///< In game menu
};


#endif /* !PLAYER_HH_ */
