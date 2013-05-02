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
  Font();
  Font(const std::string file_name,
		const std::string name,
		unsigned int id);

  ~Font();

  bool load();
  void unload();


private:
  sf::Font *_font; ///< actual Font
};

#endif /* !FONT_HH_ */
