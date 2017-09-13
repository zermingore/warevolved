/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief On Screen Debug information display
 */

#ifndef DEBUG_OSD_HH_
# define DEBUG_OSD_HH_

# include <string>
# include <memory>
# include <vector>
# include <type_traits>

# include <common/using.hh>


namespace sf
{
  class Drawable;
}

namespace resources {
  class Text;
}



namespace debug {


/**
 * \class OSD
 * \brief Provides a way to display debug data in the game window
 * \todo Watch a variable
 *
 * The On Screen Debug will draw in the Graphics Engine window
 * though the display will be done by the Graphics Engine
 */
class OSD
{
public:
  /**
   * \brief Adds data as a string to display, placing it automatically
   * \param str String to display
   * \param description Optional argument to put in front of the data string
   * \note The placement is made according to _dataPosition
   * \note If the description is given, it will be followed by the string ": "
   */
  static void addStr(const std::string str, const std::string description = "");

  /**
   * \brief Adds data as a Plain Old Data to display, placing it automatically
   * \param value value to display *must* be an integral, Plain Old Data type
   * \param description Optional argument to put in front of the data
   * \note The placement is made according to _dataPosition
   * \note If the description is given, it will be followed by the string ": "
   */
  template<typename T>
  static void addPod(const T& value, const std::string description = "");

  /**
   * \brief Draw added data, calling the Graphics Engine
   */
  static void draw();


private:
  /**
   * \brief Builds and return an initialized label, to display text
   * \return a pointer to the new label
   */
  static void addText(const std::string str);


  static unsigned int _fontSize; ///< Text font size
  static Coords _dataPosition;   ///< Coordinates where to display data

  ///< List of items to display
  static std::vector<std::shared_ptr<sf::Drawable>> _drawables;
};



template<typename T>
void OSD::addPod(const T& value, const std::string description)
{
  static_assert(std::is_pod<T>::value,
                "OSD::addPod supports only Plain Old Data");

  std::string desc;
  if (description != "")
  {
    desc = description + ": ";
  }

  addText(desc + std::to_string(value));
}


} // namespace debug


#endif /* !DEBUG_OSD_HH_ */
