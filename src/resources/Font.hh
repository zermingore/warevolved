#ifndef FONT_HH_
# define FONT_HH_

# include <resources/Resource.hh>
# include <common/include.hh>


/** \brief Font Resource type
 ** Derived from Resource
 */

class Font : public Resource
{
public:
  Font() {}

  /** \brief Constructor
   ** \param file_name font file name
   ** \param name font alias
   */
  Font(const std::string file_name,
       const std::string name,
       unsigned int id);

  /// \brief Destructor
  ~Font();

  bool load();
  void unload();

  /** \brief font getter
   ** \return _font value
   */
  sf::Font *getFont();

private:
  sf::Font *_font; ///< current Font
};

#endif /* !FONT_HH_ */
