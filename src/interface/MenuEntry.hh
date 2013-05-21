#ifndef MENUENTRY_HH_
# define MENUENTRY_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>


class MenuEntry
{
public:
  /** \brief default Constructor
   */
  MenuEntry();

  /** \brief Constructor
   */
  explicit MenuEntry(std::string label_name);

  /** \brief Destructor
   */
  ~MenuEntry();


  /** \brief displays the entry at position
   ** \param position where the entry will be display
   */
  void draw(sf::Vector2f position);


private:
  Image *_background; ///< background image
  sf::Text* _label; ///< button label text
  Font *_font; ///< button label font
};

#endif /* !MENUENTRY_HH_ */
