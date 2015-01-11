#ifndef INTERFACEELEMENT_HH_
# define INTERFACEELEMENT_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>


class InterfaceElement
{
public:
  virtual void draw();


protected:
  InterfaceElement() {};
  sf::Vector2f _position; ///< Element position
  Image _background; ///< background image
  std::shared_ptr<sf::Text> _label; ///< label text
  Font _font; ///< label font
};

#endif /* !INTERFACEELEMENT_HH_ */
