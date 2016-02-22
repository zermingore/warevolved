/*
 * game/Player.hh
 *
 *  Created on: August 1, 2013
 *      Author: Zermingore
 */

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <memory>
# include <common/structures/Vector.hh> // for Color
# include <interface/Interface.hh>


class Interface;


/** \class Player class
 * a player can be control by human or AI
 */
class Player
{
public:
  /**
   * \brief Constructor
   *
   * Sets the Player's index to a unique value.
   */
  Player();

  // __________________________ Getters / Setters __________________________ //
  /**
   * \brief Player identifier getter.
   * \return Player's identifier.
   */
  size_t id() { return _id; }

  /**
   * \brief Cursor color getter.
   * \return Color of the cursor.
   */
  Color cursorColor() { return _cursorColor; }

  /**
   * \brief Player's units color getter.
   * \return Units color.
   */
  Color unitsColor() { return _unitsColor; }

  /**
   * \brief Player's interface getter.
   * \return Interface pointer.
   */
  std::shared_ptr<Interface> interface() { return _interface; }

  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(Color color) { _cursorColor = color; }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(Color color) { _unitsColor = color; }


private:
  // (logicaly const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player's identifier
  std::shared_ptr<Interface> _interface; ///< Interface (menu status, ...)
  Color _cursorColor; ///< Cursor's color
  Color _unitsColor;  ///< Units color
};

#endif /* !PLAYER_HH_ */
