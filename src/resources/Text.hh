/**
 * \file
 * \author Zermingore
 * \date Sept 11, 2017
 * \namespace resources
 * \brief Text class declaration, used to draw strings
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
class Text final: public Resource
{
public:
  /**
   * \brief Default Constructor
   */
  Text() = delete;

  /**
   * \brief Constructor. Initializes a Text, ready to draw
   * \param str Text content
   * \param size Size of the text, in pixels
   * \param pos Optional position of the text on the screen
   * \param font Optional font name used to retrieve the Font
   */
  Text(const std::string& str,
       size_t size,
       graphics::Pos2 pos = {0, 0},
       const std::string& font = "");


  /**
   * \note Entity's local bounding rectangle getter
   * \return Graphical text 'size'
   * \note Wrapper around sf::Text::getLocalBounds()
   */
  graphics::Size2 getSize();

  /**
   * \brief Position setter
   * \note Does not call draw automatically
   * \param pos New position
   */
  void setPosition(graphics::Pos2 pos);

  /**
   * \brief Position setter
   * \note Does not call draw automatically
   * \param x New column position
   * \param y New line position
   */
  void setPosition(graphics::component x, graphics::component y);

  /**
   * \brief Graphic text getter
   * \return The graphical element containing the Text
   */
  const auto& graphicalText() const { return _text; }

  /**
   * \brief Draw the Text
   */
  void draw();



private:
  std::string _string;             ///< Text content
  size_t _size;                    ///< Text size (in pixels)
  std::shared_ptr<Font> _font;     ///< Graphical Font used to draw the text
  std::shared_ptr<sf::Text> _text; ///< Graphical object representing the Text
};


} // namespace resources


#endif /* !RESOURCES_TEXT_HH_ */
