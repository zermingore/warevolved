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
class OptionsParser;

enum class e_units;


/**
 * \class Battle
 * \brief A battle is a game, launched from the Game class.
 */
class Battle
{
public:
  /**
   * \brief Deleted default Constructor
   */
  Battle() = delete;

  /**
   * \brief Constructor; Loads the given map if any
   * \param options_parser Command line options parser
   */
  explicit Battle(const OptionsParser& options_parser);


  /**
   * \brief Initialize a new map (including the players)
   * \note Calls buildMap() buildPlayers()
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

  /// Initializes the map, adding the terrains, units, ...
  void buildMap();

  /**
   * \brief Parse the map file in order to load it
   * \note Loads the _loadMapFile map
   * \note Populates the _map
   */
  void loadMap();

  /**
   * \brief Generates a random Map
   * \note Populates the _map
   */
  void generateRandomMap();

  /**
   * \brief Save the current map in the _savesDirectory folder
   * \note _savesDirectory is the current folder (./) or,
   *   if provided through command line arguments, in the saves_directory folder
   */
  void saveMap();


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
  void initializePlayers();

  /**
   * \brief Place each Player's Cursor on one of its Unit
   *   make sure that every Player has at least 1 Unit which did not play yet
   */
  void randomMapRefine();


  std::vector<std::shared_ptr<Player>> _players; ///< players in this battle
  size_t _currentPlayer; ///< current player's id
  size_t _nbPlayers; ///< Number of players
  std::shared_ptr<Map> _map; ///< Map of this battle
  std::string _loadMapFile; ///< File from where the map will be loaded
  mutable std::string _savesDirectory; ///< Where to save maps
};

#endif /* !BATTLE_HH_ */
