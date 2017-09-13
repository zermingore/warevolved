/**
 * \file
 * \date Sept 11, 2017
 * \brief Text declaration, used to draw a string on the screen
 */


#ifndef RESOURCES_TEXT_HH_
# define RESOURCES_TEXT_HH_

# include <string>
# include <memory>

# include <graphics/graphic_types.hh>
# include <resources/Resource.hh>



namespace resources {


class Font;


/**
 * \class Text
 * \brief Class representing a text; uses a Font
 */
class Text: public Resource
{
public:
  /**
   * \brief Default Constructor
   */
  Text() = default;


  /**
   * \brief Constructor. Initializes a Text, ready to draw
   * \param str Text content
   * \param size Size of the text, in pixels
   * \param pos Position of the text on the screen
   * \param font Optional font name used to retrieve the Font
   */
  Text(std::string str, int size, graphics::Pos2 pos, std::string font = "");


  /**
   * \brief Position setter. Does not call draw automatically
   * \param pos New position
   */
  void setPosition(graphics::Pos2 pos) { _position = pos; }


  /**
   * \brief Graphic text getter
   * \return The graphical element containing the Text
   */
  auto graphicalText() const { return _text; }


  /**
   * \brief Draw the Text
   */
  void draw();



private:
  std::string _string;             ///< Text content
  size_t _size;                    ///< Text size (in pixels)
  graphics::Pos2 _position;        ///< Position on the screen
  std::shared_ptr<Font> _font;     ///< Graphical Font used to draw the text
  std::shared_ptr<sf::Text> _text; ///< Graphical object representing the Text
};


} // namespace resources


#endif /* !RESOURCES_TEXT_HH_ */
