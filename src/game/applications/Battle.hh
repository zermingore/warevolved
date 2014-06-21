/*
 * game/Applications/Battle.hh
 *
 *  Created on: August 3, 2013
 *      Author: Zermingore
 */

#ifndef BATTLE_HH_
# define BATTLE_HH_

# include <game/applications/Application.hh>
# include <game/Player.hh>
# include <game/Map.hh>


/** \class Battle
 ** a battle is a game, launched from the Game class
 */
class Battle: public Application
{
public:
  // TODO add filename XOr nb players, ...

  /** \brief Default Constructor
   ** builds a random battle
   ** with a random number of players, units, ...
   */
  Battle();

  /** \brief initializes a Battle
   ** calls buildPlayers, buildMap, buildUnits
   */
  void init();

  /** \brief players vector getter
   ** \return _players vector
   */
  inline std::vector<std::shared_ptr<Player>> const players() { return _players; }

  /** \brief _players[id] getter
   ** \param id Player's id to retrieve
   ** \return the Player which number is \param id
   */
  inline std::shared_ptr<Player> getPlayer(const unsigned int &id)
  { return _players[id]; }

  /** \brief _map getter
   ** \return a reference to the map
   */
  inline Map map() { return _map; }

  /** \brief builds a new unit of type \param unit
   ** \param unit type of the new unit
   */
  void newUnit(e_unit unit);

  /** \brief Switches to the next player
   **   adapt cursor color
   **   sets cursor's position to the
   **     last known position of the new current faction
   */
  void nextPlayer();

  /** \brief initializes map
   */
  void buildMap();


private:
  /** \brief initializes players
   */
  void buildPlayers();

  /** \brief initializes units
   */
  void buildUnits();


  std::vector<std::shared_ptr<Player>> _players; ///< players in this battle
  Map _map; ///< Map of this battle
  unsigned int _currentPlayer; ///< current player's id
};

#endif /* !BATTLE_HH_ */
