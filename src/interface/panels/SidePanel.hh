#ifndef SIDE_PANEL_HH_
# define SIDE_PANEL_HH_

# include <interface/panels/Panel.hh>


/** \brief Side Panel possible positions
 */
enum class Panel_position
{
  DEACTIVATED, // must be the first one (see ++ overloading)
  LEFT,
  RIGHT,

  END_OF_ENUM // useful for increment operator
};


// defining increment operator
Panel_position& operator++(Panel_position& pos);
Panel_position operator++(Panel_position& pos, int);


/** \class SidePanel class
 ** Interface side panel management
 */
class SidePanel: public Panel
{
public:
  SidePanel();

  inline Panel_position position() { return _position; }; ///< _position getter
  Panel_position incrementPosition();
  /** \brief increments position, returns the *PREVIOUS* one
   ** \return actual position, before incrementing it
   */

  void draw();


private:
  Panel_position _position; ///< current position (deactivcated, left, right)
};

#endif /* !SIDE_PANEL_HH_ */
