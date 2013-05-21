#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/SelectionMenu.hh>

class Interface
{
public:
  /** Default Constructor
   ** Initializes _selectionMenu
   */
  Interface();

  /** Destructor
   */
  ~Interface();

  /** \return _selectionMenu
   */
  SelectionMenu *getSelectionMenu();

private:
  SelectionMenu *_selectionMenu; ///< in game selection menu
};

#endif /* !INTERFACE_HH_ */
