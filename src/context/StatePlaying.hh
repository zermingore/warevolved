/**
 * \file
 * \date October 14, 2016
 * \author Zermingore
 */

#ifndef STATE_PLAYING_HH_
# define STATE_PLAYING_HH_

# include <context/State.hh>

class StatePlaying: public State
{
public:
  /// registers to callbacks
  StatePlaying();
  void moveCursor(); // add param ?

  std::vector<int> getAttrList();
};


#endif /* !STATE_PLAYING_HH_ */
