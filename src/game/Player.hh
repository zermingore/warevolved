/**
 * \file
 * \date August 1, 2013
 * \author Zermingore
 * \brief Player definition.
 */

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <memory>

# include <common/using.hh>
# include <graphics/graphic_types.hh>


namespace interface {
  class Interface;
  class Cursor;
  class Panel;
}

class Unit;


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
  explicit Player(const graphics::Color c);


  /**
   * \brief Player identifier getter.
   * \return Player's identifier.
   */
  auto id() { return _id; }


  // Cursor motion
  void moveCursorUp();
  void moveCursorDown();
  void moveCursorLeft();
  void moveCursorRight();

  /**
   * \brief callback when a cell is clicked.
   * \note only used when no unit is selected / menu opened
   */
  void select();

  /**
   * \brief color getter
   * \return the color associated to the player
   */
  auto color() { return _color; }

  /**
   * \brief Player's interface getter.
   * \return Interface pointer.
   */
  auto interface() { return _interface; }

  /**
   * \brief Cursor getter.
   * \return a pointer to the player's cursor.
   */
  auto cursor() { return _cursor; }

  /**
   * \brief _cellCursorPosition getter
   * \note Is not always the interface cursor
   * \note is not touched in a menu state (but in moving state for instance)
   * \return Holographic cursor position getter
   */
  auto cellCursorPosition() const { return _cellCursorPosition; }

  /**
   * \brief Set the currently browsed cell position
   * \note Useful, for instance, when moving a unit without moving the cursor
   */
  void setCellCursorPosition(const Coords coords) {
    _cellCursorPosition = coords;
  }

  /**
   * \brief Reset the currently browsed cell position
   */
  void resetCellCursorPosition();

  /**
   * \brief Toggle the side panel status (Left, Right, Deactivated)
   * \note The request is forwarded to the Panel itself
   */
  void togglePanel();

  /**
   * \brief Update the Map selected Unit
   */
  void updateSelectedUnit();


private:
  /**
   * \brief Keep updated the real cursor position
   */
  void updateCellCursorPostion();


  // (logically const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player's identifier

  // interface
  std::shared_ptr<interface::Interface> _interface; ///< User Interface
  std::shared_ptr<interface::Cursor>    _cursor;    ///< Map Cursor
  std::shared_ptr<interface::Panel>     _panel;     ///< Side panel

  std::shared_ptr<Unit> _selectedUnit; ///< Current selected unit

  Coords _cellCursorPosition; ///< Current browsed cell

  graphics::Color _color; ///< player's color
};


#endif /* !PLAYER_HH_ */
