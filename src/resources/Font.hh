/**
 * \file
 * \date Apr 27, 2013
 * \author Zermingore
 */

#ifndef RESOURCES_FONT_HH_
# define RESOURCES_FONT_HH_

# include <string>
# include <memory>

# include <resources/Resource.hh>
# include <graphics/graphic_types.hh>


namespace resources {


/**
 * \class Font
 * \brief Font resource type, used to draw text
 */
class Font: public Resource
{
public:
  /// \brief default constructor
  Font() = default;

  /**
   * \brief Constructor
   * \param file_name font file name
   * \param name font alias
   */
  Font(const std::string& file_name, const std::string& name);

  /**
   * \brief _font getter
   * \return _font value
   * \note loads the requested Font if needed
   */
  std::shared_ptr<graphics::Font> getFont();


private:
  std::shared_ptr<graphics::Font> _font; ///< current Font
};


} // namespace resources



#endif /* !RESOURCES_FONT_HH_ */
