#ifndef PLAYER_HH_
# define PLAYER_HH_

/**
 * \file Player definition.
 * \date August 1, 2013
 * \author Zermingore
 */

# include <memory>
# include <interface/Interface.hh>

class Interface;


/**
 * \class Player
 * \brief A player can be control by human or AI.
 */
class Player
{
public:
  /**
   * \brief Constructor
   *
   * Sets the Player's index to a unique value.
   */
  Player();


  /**
   * \brief Player identifier getter.
   * \return Player's identifier.
   */
  size_t id() { return _id; }

  /**
   * \brief Player's interface getter.
   * \return Interface pointer.
   */
  std::shared_ptr<interface::Interface> interface() { return _interface; }


private:
  // (logicaly const, cannot be initialized by a static variable)
  mutable size_t _id; ///< Player's identifier
  std::shared_ptr<interface::Interface> _interface; ///< User Interface
};

#endif /* !PLAYER_HH_ */
