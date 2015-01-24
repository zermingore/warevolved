#ifndef MENUBAR_HXX_
# define MENUBAR_HXX_

// Operators definitions

// pre-incrementation
MenuBar_position& operator++(MenuBar_position& pos)
{
  pos = static_cast<MenuBar_position> (static_cast<int> (pos) + 1);
  if (pos == MenuBar_position::END_OF_ENUM)
    pos = MenuBar_position::DEACTIVATED;

  return pos;
}

// post-incrementation
MenuBar_position operator++(MenuBar_position& pos, int)
{
  // using pre-incrementation
  return ++pos;
}

#endif // !MENUBAR_HXX_
