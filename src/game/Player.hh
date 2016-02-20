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
   * sets the Player's index to a unique value
   */
  Player();

  size_t id() { return _id; }

  // __________________________ Getters / Setters __________________________ //
  /**
   * \brief cursor color getter
   * \return color of the cursor (_cursorColor)
   */
  Color cursorColor() { return _cursorColor; }

  /**
   * \brief units color getter
   * \return units color (_unitsColor)
   */
  Color unitsColor() { return _unitsColor; }

  std::shared_ptr<Interface> interface() { return _interface; }

  /**
   * \brief sets cursor color
   * \param color _cursorColor value
   */
  void setCursorColor(Color color) { _cursorColor = color; }

  /**
   * \brief sets units color
   * \param color units color
   */
  void setUnitsColor(Color color) { _unitsColor = color; }


private:
  // (logicaly const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player identifier
  std::shared_ptr<Interface> _interface; ///< interface (menu status, ...)
  Color _cursorColor; ///< cursor's color
  Color _unitsColor; ///< units color
};

#endif /* !PLAYER_HH_ */
