#ifndef RESOURCES_FONT_HH_
# define RESOURCES_FONT_HH_

# include <resources/Resource.hh>
# include <common/include.hh>


namespace resources {


/**
 * \class Font Resource type
 * \brief Font class to draw text
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
  Font(const std::string file_name, const std::string name);

  /**
   * \brief Loads a font, if needed
   * \return true if the font was already loaded
   *   false if it was loaded during this call
   */
  bool load();

  /**
   * \brief _font getter
   *   loads the requested Font if needed
   * \return _font value
   */
  std::shared_ptr<sf::Font> getFont();


private:
  std::shared_ptr<sf::Font> _font; ///< current Font
};


} // namespace resources

#endif /* !RESOURCES_FONT_HH_ */
