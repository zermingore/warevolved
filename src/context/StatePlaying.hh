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
  // Cursor motion
  void moveCursorLeft();
  void moveCursorRight();
  void moveCursorDown();
  void moveCursorUp();
  // void moveCursor(); // add param ? (issue: input cb: std::function<void()>)
};


#endif /* !STATE_PLAYING_HH_ */
