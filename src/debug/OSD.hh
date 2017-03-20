/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief On Screen Debug information display
 */

#ifndef DEBUG_OSD_HH_
# define DEBUG_OSD_HH_

# include <common/include.hh>
# include <common/using.hh>


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
   *
   * The placement is made according to _dataPosition
   * \param str string to display
   */
  static void addData(const std::string str);

  /**
   * \brief Adds data as an integer to display, placing it automatically
   *
   * The placement is made according to _dataPosition
   * \param value value to display
   */
  static void addData(const int value);

  /**
   * \brief Draw added data, calling the Graphics Engine
   */
  static void draw();


private:
  /**
   * \brief Builds and return an initialized label, to display text
   * \return a pointer to the new label
   */
  static std::shared_ptr<sf::Text> text(const std::string str);


  static unsigned int _fontSize; ///< Text font size
  static Coords _dataPosition;   ///< Coordinates where to display data

  ///< List of items to display
  static std::vector<std::shared_ptr<sf::Drawable>> _drawables;
};



} // namespace debug

#endif /* !DEBUG_OSD_HH_ */
