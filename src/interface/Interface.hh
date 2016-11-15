#ifndef INTERFACE_HH_
# define INTERFACE_HH_

/**
 * \file
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

# include <vector>
# include <interface/InterfaceElement.hh>
# include <interface/InterfaceSettings.hh>


namespace interface {

class Menu;


/**
 * \class Interface
 * \brief Keeps data relative to the user's interface.
 */
class Interface
{
public:
  /// Deleted default constructor.
  Interface() = delete;

  /// Constructor. Initializes interface settings (colors, ...)
  explicit Interface(Color c);

  /**
   * \brief Sets all element to draw.
   *
   * Sets coordinates of each elements.
   */
  void buildElements();

  /**
   * \brief Adds an InterfaceElement to manage
   * \param elt Element to add to the interface
   */
  void addElement(std::shared_ptr<InterfaceElement> elt);

  /**
   * \brief Remove a managed InterfaceElement
   * \param elt Element to remove from the interface.
   */
  void removeElement(std::shared_ptr<InterfaceElement> elt);

  /**
   * \brief Interface elements vector getter.
   * \return Elements of the interface.
   */
  std::vector<std::shared_ptr<InterfaceElement>>& elements() { return _elts; }


  /**
   * \brief Returns the first InterfaceElement which name is name
   * \param name name of the InterfaceElement to retrieve
   * \return a pointer to the matching InterfaceElement, nullptr if there is none
   */
  const std::shared_ptr<InterfaceElement> element(const std::string id);

  /**
   * \brief Cursor color getter.
   * \return Color of the cursor.
   */
  Color cursorColor() const { return _settings->cursorColor(); }

  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(Color color) { _settings->setCursorColor(color); }


  /**
   * \brief Player's units color getter.
   * \return Units color.
   */
  Color unitsColor() const { return _settings->unitsColor(); }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(Color color) { _settings->setUnitsColor(color); }


  /**
   * \brief sets current menu.
   * \param menu new current menu.
   */
  std::shared_ptr<Menu> currentMenu() { return _menu; }

  /**
   * \brief sets current menu.
   * \param menu new current menu.
   */
  void setCurrentMenu(std::shared_ptr<Menu> menu) { _menu = menu; }




private:
  std::vector<std::shared_ptr<InterfaceElement>> _elts; ///< list of elements
  std::unique_ptr<InterfaceSettings> _settings; ///< interface settings
  std::shared_ptr<Menu> _menu; ///< current menu getter
};


} // namespace interface

#endif /* !INTERFACE_HH_ */
