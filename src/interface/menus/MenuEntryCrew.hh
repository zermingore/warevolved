/**
 * \file
 * \date September 21, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuEntryCrew class declaration
 */


#ifndef MENU_ENTRY_CREW_HH_
# define MENU_ENTRY_CREW_HH_

# include <string>
# include <memory>
# include <functional>

# include <interface/menus/MenuEntry.hh>
# include <interface/InterfaceElement.hh>
# include <game/units/Unit.hh> // e_unit_role


namespace resources {
  class Text;
}

class Vehicle;


namespace interface {


/**
 * \class MenuEntryCrew
 * \brief One entry (a Crew Member) of a MenuCrewBrowse
 * \note The entry position is relative to the menu it belongs to.
 * \note Motherclass: MenuEntry
 */
class MenuEntryCrew final: public MenuEntry
{
public:
  /**
   * \brief Constructor
   * \param crew_idx Crew member array index
   */
  explicit MenuEntryCrew(const e_entry entry, int crew_idx = -1);


  /**
   * \brief returns entry Identifier, as an e_entry value
   * \return entry identifier
   */
  auto id() const { return _id; }

  /**
   * \brief Executes the action matching the entry
   */
  void execute() const;

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


  e_unit_role _role;                 ///< Crew member role, used as label
  std::shared_ptr<Vehicle> _vehicle; ///< Holder of the crew
  const int _crewIdx;                ///< Crew member array index
};


} // namespace interface


#endif /* !MENU_ENTRY_CREW_HH_ */
