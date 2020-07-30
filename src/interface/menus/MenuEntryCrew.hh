/**
 * \file
 * \date September 21, 2019
 * \author Zermingore
 * \brief interface::MenuEntryCrew declaration
 */


#ifndef MENU_ENTRY_CREW_HH_
# define MENU_ENTRY_CREW_HH_

# include <string>
# include <memory>
# include <functional>

# include <interface/menus/MenuEntry.hh>
# include <interface/InterfaceElement.hh>
# include <game/units/unit_roles.hh>


namespace resources {
  class Text;
}


namespace interface {


/**
 * \class MenuEntryCrew
 * \brief One entry (a Crew Member) of a MenuCrewBrowse
 * \note The entry position is relative to the menu it belongs to.
 * \note Motherclass: MenuEntry
 */
class MenuEntryCrew: public MenuEntry
{
public:
  /**
   * \brief deleted default constructor
   */
  MenuEntryCrew() = delete;

  /**
   * \brief Constructor
   * \param entry Entry type to build.
   */
  explicit MenuEntryCrew(const e_entry entry);

  /**
   * \brief Constructor
   * \param role Crew member role
   * \param crew_member Crew member this entry is about
   */
  MenuEntryCrew(e_unit_role role,
                std::shared_ptr<const Unit> crew_member);


  /**
   * \brief returns entry Identifier, as an e_entry value
   * \return entry identifier
   */
  auto id() const { return _id; }

  /**
   * \brief Executes the action matching the entry
   */
  void execute();

  /**
   * \brief _callback setter
   * \param callbacks List of Callbacks called when the menu entry is selected
   */
  void setCallbacks(const std::vector<std::function<void()>>& callbacks) {
    _callbacks = callbacks;
  }

  /**
   * \brief _callback setter
   * \param callback Callback called when the menu entry is selected
   */
  void setCallback(const std::function<void()> callback) {
    _callbacks = { callback };
  }

  /**
   * \brief updates the graphical attributes of the entry
   */
  void update() override final;

  /**
   * \brief Draws label and sprite of the entry, calling the graphics engine
   */
  void draw() override final;


  /// _role getter
  e_unit_role role() const { return _role; }



private:
  /**
   * \brief Initializes the label name
   */
  void setLabelName();

  /// Pointer on the Unit in the crew this entry is about
  const std::shared_ptr<const Unit> _crewMember;

  const e_unit_role _role; ///< Crew member role, used as label
};


} // namespace interface


#endif /* !MENU_ENTRY_CREW_HH_ */
