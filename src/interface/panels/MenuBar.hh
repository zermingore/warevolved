#ifndef MENU_BAR_HH_
# define MENU_BAR_HH_

# include <interface/panels/Panel.hh>


/** \brief Menu Bar possible positions
 */
enum class MenuBar_position
{
  DEACTIVATED, // must be the first one, (see ++ overloading)
  TOP,
  BOTTOM, // not sure we'll allow this

  END_OF_ENUM // useful for increment operator
};


// defining increment operator
MenuBar_position& operator++(MenuBar_position& pos);
MenuBar_position operator++(MenuBar_position& pos, int);


class MenuBar: public Panel
{
public:
  MenuBar(); ///< Default constructor

  inline MenuBar_position position() { return _position; }; ///< _position getter
  /** \brief increments position, returns the *PREVIOUS* one
   ** \return actual position, before incrementing it
   */
  MenuBar_position incrementPosition();

  void draw();


private:
  MenuBar_position _position; ///< current position
};

#endif /* !MENU_BAR_HH_ */
