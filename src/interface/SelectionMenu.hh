#ifndef SELECTIONMENU_HH_
# define SELECTIONMENU_HH_

# include <interface/EntriesMenu.hh>

/** \brief in-game SelectionMenu class
 */
class SelectionMenu : public EntriesMenu
{
public:
  SelectionMenu();
  ~SelectionMenu();

  /** \brief builds the selection menu, filling _entries
   */
  void build();

  /** \brief executes action matching _selectedEntry
   */
  void executeEntry();
};

#endif /* !SELECTIONMENU_HH_ */
