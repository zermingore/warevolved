/*
 * game/Applications/Battle.hh
 *
 *  Created on: August 3, 2013
 *      Author: Zermingore
 */

#ifndef BATTLE_HH_
# define BATTLE_HH_

# include <vector>
# include <memory>
# include <game/applications/Application.hh>
# include <common/enums/units.hh>
# include <common/structures/Vector.hh>

class Map;
class Player;


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
  std::vector<std::shared_ptr<Player>> const players();

  /** \brief _players[id] getter
   ** \param id Player's id to retrieve
   ** \return the Player which number is \param id
   */
  inline std::shared_ptr<Player> getPlayer (const size_t &id) const
  { return _players[id]; }

  /** \brief _map getter
   ** \return a reference to the map
   */
  inline std::shared_ptr<Map> map() { return _map; }

  /** \brief Switches to the next player
   **   adapt cursor color
   **   sets cursor's position to the
   **     last known position of the new current faction
   */
  void nextPlayer();

  /** \brief initializes map
   */
  void buildMap();


  /** \brief current player identifier getter
   ** \return _currentPlayer: current player identifier
   */
  inline size_t currentPlayer() { return _currentPlayer; }

  /** \brief sets _currentPlayer
   ** \param id new current player identifier
   */
  inline void setCurrentPlayer(size_t id) { _currentPlayer = id; }


private:
  /** \brief initializes players
   */
  void buildPlayers();

  /** \brief initializes units
   */
  void buildUnits();

  std::vector<std::shared_ptr<Player>> _players; ///< players in this battle
  std::shared_ptr<Map> _map; ///< Map of this battle
  size_t _currentPlayer; ///< current player's id
};

#endif /* !BATTLE_HH_ */
