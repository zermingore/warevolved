#ifndef FONT_HH_
# define FONT_HH_

# include <resources/Resource.hh>
# include <common/include.hh>


/** \class Font Resource type
 * Derived from Resource
 */
class Font : public Resource
{
public:
  /// \brief default constructor
  Font() {}

  /**
   * \brief Constructor
   * \param file_name font file name
   * \param name font alias
   */
  Font(const std::string file_name,
       const std::string name);

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

#endif /* !FONT_HH_ */
