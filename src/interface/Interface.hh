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


/**
 * \class Interface
 * \brief Keeps data relative to the user's interface.
 */
class Interface
{
public:
  /// Deleted default constructor.
  Interface() = delete;

  /// Constructor. Initializes in-game menu.
  explicit Interface(Color c);

  /**
   * \brief Sets all element to draw.
   *
   * Sets coordinates of each elements.
   */
  void buildElements();

  /**
   * \brief Update every elements parameters.
   */
  void updateElements();

  /**
   * \brief Adds an InterfaceElement to manage
   * \param elt Element to add to the interface
   */
  void addElement(std::shared_ptr<InterfaceElement> elt);

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
   * \brief Player's units color getter.
   * \return Units color.
   */
  Color unitsColor() const { return _settings->unitsColor(); }

  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(Color color) { _settings->setCursorColor(color); }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(Color color) { _settings->setUnitsColor(color); }


private:
  std::vector<std::shared_ptr<InterfaceElement>> _elts; ///< list of elements
  std::unique_ptr<InterfaceSettings> _settings; ///< interface settings
};


} // namespace interface

#endif /* !INTERFACE_HH_ */
