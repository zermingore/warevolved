/*
 * game/Player.hh
 *
 *  Created on: August 1, 2013
 *      Author: Zermingore
 */

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <common/enums/units.hh>
# include <game/Unit.hh>


/** \brief Faction enum
 ** list of factions
 */
enum e_factions
{
  E_FACTION_T,
  E_FACTION_Z,
  E_FACTION_P, // we could have put a, b, c
  E_FACTION_NEUTRAL,

  E_FACTION_NB_FACTIONS
};


/** \brief Player class
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
  void setunitsColor(Color color);

  /** \brief Saves current cursor position
   */
  void saveCursorPosition();

  /** \brief adds a unit to the player's units list
   ** \param unit unit to add to the player's list
   */
  void addUnit(Unit &unit);

  /** \brief builds a new Unit and adds it to the player's units list
   ** \param unit type of the unit to add to the player's list
   ** \param line line location of the new Unit
   ** \param column column location of the new Unit
   */
  Unit &newUnit(e_units unit, unsigned int line = 0, unsigned int column = 0);

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
};

#endif /* !PLAYER_HH_ */
