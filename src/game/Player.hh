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

class Interface;


/** \class Player class
 ** a player can be control by human or AI
 */
class Player
{
public:
  /** \brief Constructor
   ** sets the Player's index to a unique value
   */
  Player();

  // __________________________ Getters / Setters __________________________ //
  /** \brief cursor color getter
   ** \return color of the cursor (_cursorColor)
   */
  inline Color cursorColor() { return _cursorColor; }

  /** \brief units color getter
   ** \return units color (_unitsColor)
   */
  inline Color unitsColor() { return _unitsColor; }

  /** \brief sets cursor color
   ** \param color _cursorColor value
   */
  inline void setCursorColor(Color color) { _cursorColor = color; }

  /** \brief sets units color
   ** \param color units color
   */
  inline void setUnitsColor(Color color) { _unitsColor = color; }


private:
  size_t _id;
//  std::unique_ptr<Interface> _interface; ///< interface (menu status, ...)
  Color _cursorColor; ///< cursor's color
  Color _unitsColor; ///< units color
};

#endif /* !PLAYER_HH_ */
