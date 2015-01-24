#ifndef SIDE_PANEL_HXX_
# define SIDE_PANEL_HXX_

// Operators definitions

// pre-incrementation
Panel_position& operator++(Panel_position& pos)
{
  pos = static_cast<Panel_position> (static_cast<int> (pos) + 1);
  if (pos == Panel_position::END_OF_ENUM)
    pos = Panel_position::DEACTIVATED;

  return pos;
}

// post-incrementation
Panel_position operator++(Panel_position& pos, int)
{
  // using pre-incrementation
  return ++pos;
}

#endif // !SIDE_PANEL_HXX_
