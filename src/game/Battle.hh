/**
 * \file
 * \date August 3, 2013
 * \author Zermingore
 * \brief Battle class declaration
 */

#ifndef BATTLE_HH_
# define BATTLE_HH_

# include <vector>
# include <memory>
# include <structures/Vector.hh>

class Map;
class Player;

enum class e_units;


/**
 * \class Battle
 * \brief A battle is a game, launched from the Game class.
 */
class Battle
{
public:
  /// \todo add filename XOr nb players, ...

  /**
   * \brief Default Constructor
   *
   * Builds a random battle.
   * with a random number of players, units, ...
   * Calls buildPlayers(), buildMap()
   */
  Battle();


  /**
   * \brief Initialize a new map (including the players)
   */
  void initializeMap();

  /**
   * \brief Players vector getter.
   * \return Players list.
   */
  auto players() const { return _players; }

  /**
   * \brief _players[id] getter.
   * \param id Player's id to retrieve.
   * \return Player which number match the given id.
   */
  std::shared_ptr<Player> getPlayer(const size_t &id) const {
    return _players[id];
  }

  /**
   * \brief Map getter.
   * \return A pointer to the map.
   */
  auto map() { return _map; }

  /// End Player turns. Switch to the next player.
  void nextPlayer();

  /// Initializes the map, adding the units.
  void buildMap();

  /**
   * \brief Parse the given file in order to load the map
   * \param file_name XML file to parse
   * \return A pointer on the freshly created map
   */
  std::shared_ptr<Map> loadMap(const std::string& file_name);

  /**
   * \brief Save the current map in the given filename
   * \param file_name file where to save the Map
   */
  void saveMap(const std::string& file_name);


  /**
   * \brief current player getter
   * \return a pointer on the current player
   */
  std::shared_ptr<Player> getCurrentPlayer() {
    return _players[_currentPlayer];
  }

  /**
   * \brief current player's identifier getter
   * \return Current player's identifier.
   */
  auto currentPlayer() { return _currentPlayer; }

  /**
   * \brief sets _currentPlayer
   * \param id new current player identifier
   */
  void setCurrentPlayer(size_t id) { _currentPlayer = id; }


private:
  /// Initializes players.
  void buildPlayers();

  std::vector<std::shared_ptr<Player>> _players; ///< players in this battle
  std::shared_ptr<Map> _map; ///< Map of this battle
  size_t _currentPlayer; ///< current player's id
};

#endif /* !BATTLE_HH_ */
