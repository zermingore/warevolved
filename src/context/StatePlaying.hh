/**
 * \file
 * \date October 14, 2016
 * \author Zermingore
 */

#ifndef STATE_PLAYING_HH_
# define STATE_PLAYING_HH_

# include <context/State.hh>


/**
 * \class StatePlaying
 * \brief Represents the default playing State (on the map, without menu)
 */
class StatePlaying: public State
{
public:
  /// registers to callbacks
  StatePlaying();

  /// Aborts the execution
  std::vector<int> getAttrList();


private:
  void moveCursor(); // add param ?
};


#endif /* !STATE_PLAYING_HH_ */
