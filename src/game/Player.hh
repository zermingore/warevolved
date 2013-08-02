/*
 * game/Player.hh
 *
 *  Created on: August 1, 2013
 *      Author: Zermingore
 */

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <common/structures/Vector.hh> // FIXME tmp include (for Color)


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

  /** \brief Initializes a player
   **   adds it to the Status current playing Players list
   */
  void init();

  /** \brief cursor last known position getter
   ** \return _lastCursorPosition
   */
  Coords getLastCursorPosition();

  /** \brief return cursor color
   ** \return _cursorColor
   */
  Color getCursorColor();

  /** \brief sets cursor color
   ** \param color _cursorColor value
   */
  void setCursorColor(Color color);

  /** \brief Saves current cursor position
   */
  void saveCursorPosition();


private:
  Color _cursorColor; ///< cursor's color
  Coords _lastCursorPosition; ///< position to remember each time we hit Next Turn
};

#endif /* !PLAYER_HH_ */
