#ifndef INTERFACESETTINGS_HH_
# define INTERFACESETTINGS_HH_

/**
 * \file
 * \brief Interface settings.
 */

# include <common/using.hh>


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
   *
   * \param player_color Player's main color.
   */
  explicit InterfaceSettings(Color player_color);



  /**
   * \brief Cursor color getter.
   * \return Color of the cursor.
   */
  Color cursorColor() { return _cursorColor; }

  /**
   * \brief Player's units color getter.
   * \return Units color.
   */
  Color unitsColor() { return _unitsColor; }

  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(Color color) { _cursorColor = color; }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(Color color) { _unitsColor = color; }


private:
  Color _cursorColor; ///< Color of the Player's Cursor.
  Color _unitsColor;  ///< Color of the Player's Units.
};

} // namespace interface


#endif /* !INTERFACESETTINGS_HH_ */