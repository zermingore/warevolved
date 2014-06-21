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

  // __________________________ Getters / Setters __________________________ //
  /** \brief cursor last known position getter
   ** \return _lastCursorPosition
   */
  inline Coords lastCursorPosition() { return _lastCursorPosition; }

  /** \brief cursor color getter
   ** \return color of the cursor (_cursorColor)
   */
  inline Color cursorColor() { return _cursorColor; }

  /** \brief units color getter
   ** \return units color (_unitsColor)
   */
  inline Color unitsColor() { return _unitsColor; }

  /** \brief Units list getter
   ** \return list of player's units (_units)
   */
  std::vector<std::shared_ptr<Unit>> units() { return _units; }

  /** \brief sets cursor color
   ** \param color _cursorColor value
   */
  inline void setCursorColor(Color color) { _cursorColor = color; }

  /** \brief sets units color
   ** \param color units color
   */
  inline void setUnitsColor(Color color) { _unitsColor = color; }

  // __________________________ Member Functions __________________________ //
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
  void addUnit(std::shared_ptr<Unit> unit) { _units.push_back(unit); }

  /** \brief builds a new Unit and adds it to the player's units list
   ** \param unit type of the unit to add to the player's list
   ** \param column column location of the new Unit
   ** \param line line location of the new Unit
   */
  std::shared_ptr<Unit> newUnit(e_unit unit,
                                unsigned int column = 0, unsigned int line = 0);

  /** \brief removes a unit to the player's units list
   ** \param unit unit to remove from the player's list
   */
  void removeUnit(std::shared_ptr<Unit> unit);


private:
  unsigned int _index; ///< player's index in the Battle _players array
  Color _cursorColor; ///< cursor's color
  Color _unitsColor; ///< units color
  Coords _lastCursorPosition; ///< position to remember each time we hit Next Turn
  std::vector<std::shared_ptr<Unit>> _units; ///< units vector
  bool _isDead; ///< is the player still playing
  e_faction _faction; ///< player's faction
};

#endif /* !PLAYER_HH_ */
