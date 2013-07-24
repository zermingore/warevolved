#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/SelectionMenu.hh>
# include <interface/ActionMenu.hh>

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

  /** selection menu getter
   ** \return _selectionMenu
   */
  SelectionMenu *getSelectionMenu();

  /** action menu getter
   ** \return _actionMenu
   */
  ActionMenu *getActionMenu();


private:
  SelectionMenu *_selectionMenu; ///< in game selection menu
  ActionMenu *_actionMenu; ///< in game action menu
};

#endif /* !INTERFACE_HH_ */
