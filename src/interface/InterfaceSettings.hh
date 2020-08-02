/**
 * \file
 * \date Feb 23, 2016
 * \author Zermingore
 * \brief InterfaceSettings class declaration
 */

#ifndef INTERFACE_INTERFACE_SETTINGS_HH_
# define INTERFACE_INTERFACE_SETTINGS_HH_

# include <graphics/graphic_types.hh> // Color


namespace interface {


/**
 * \class InterfaceSettings
 * \brief User Interface settings.
 */
class InterfaceSettings
{
public:
  /// Deleted default constructor as we need a color.
  InterfaceSettings() = delete;

  /**
   * \brief InterfaceSettings constructor.
   * \param player_color Player's main color.
   */
  explicit InterfaceSettings(const graphics::Color player_color)
    : _cursorColor(player_color)
    , _unitsColor(player_color)
  {
  }

  /// Default destructor
  ~InterfaceSettings() = default;


  /**
   * \brief Cursor color getter.
   * \return Color of the cursor.
   */
  auto cursorColor() { return _cursorColor; }

  /**
   * \brief Player's units color getter.
   * \return Units color.
   */
  auto unitsColor() { return _unitsColor; }

  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(const graphics::Color color) { _cursorColor = color; }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(const graphics::Color color) { _unitsColor = color; }



private:
  graphics::Color _cursorColor; ///< Color of the Player's Cursor.
  graphics::Color _unitsColor;  ///< Color of the Player's Units.
};

} // namespace interface


#endif /* !INTERFACE_INTERFACE_SETTINGS_HH_ */
