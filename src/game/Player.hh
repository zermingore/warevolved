/*
 * game/Player.hh
 *
 *  Created on: August 1, 2013
 *      Author: Zermingore
 */

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <common/enums/units.hh>
# include <common/enums/factions.hh>
# include <game/units/Unit.hh>


/** \class Player class
 ** a player can be control by human or AI
 */
class Player
{
public:
  /** \brief Constructor
   **   builds a new Player
   */
  Player();

  /** \brief Destructor
   */
  ~Player();

  /** \brief cursor last known position getter
   ** \return _lastCursorPosition
   */
  Coords getLastCursorPosition();

  /** \brief return cursor color
   ** \return _cursorColor
   */
  Color getCursorColor();

  /** \brief units color getter
   */
  Color getUnitsColor();

  /** \brief sets cursor color
   ** \param color _cursorColor value
   */
  void setCursorColor(Color color);

  /** \brief sets units color
   ** \param color units color
   */
  void setUnitsColor(Color color);

  /** \brief Saves current cursor position
   */
  void saveCursorPosition();

  /** \brief Finished the turn of the player
   ** sets all of it's units played flag to false
   */
  void endTurn();

  /** \brief adds a unit to the player's units list
   ** \param unit unit to add to the player's list
   */
  void addUnit(Unit &unit);

  /** \brief builds a new Unit and adds it to the player's units list
   ** \param unit type of the unit to add to the player's list
   ** \param line line location of the new Unit
   ** \param column column location of the new Unit
   */
  Unit &newUnit(e_unit unit, unsigned int line = 0, unsigned int column = 0);

  /** \brief removes a unit to the player's units list
   ** \param unit unit to remove from the player's list
   */
  void removeUnit(Unit &unit);

  /** \brief Units list getter
   */
  std::vector<Unit*> getUnit() {
    return _units;
  }


private:
  unsigned int _index; ///< player's index in the Battle _players array
  Color _cursorColor; ///< cursor's color
  Color _unitsColor; ///< units color
  Coords _lastCursorPosition; ///< position to remember each time we hit Next Turn
  std::vector<Unit*> _units; ///< units vector
  bool _isDead; ///< is the player still playing
  e_faction _faction; ///< player's faction
};

#endif /* !PLAYER_HH_ */
