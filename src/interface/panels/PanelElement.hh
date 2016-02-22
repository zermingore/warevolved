#ifndef PANELELEMENT_HH_
# define PANELELEMENT_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>
# include <interface/InterfaceElement.hh>


/**
 * \brief panel elements descriptors
 */
enum e_panel
{
  E_PANEL_NONE = 0, // invalid selected panel

  E_PANEL_INFO_SELECTED_UNIT, // information about selected unit

  E_PANEL_CLOSE // closes the whole panel button
};


class PanelElement: public InterfaceElement
{
public:
//  PanelElement() = delete;
//  PanelElement(std::string label_name, e_panel entry);
  // void onClick();

//  void draw();


private:
  sf::Vector2f _position;
  sf::Vector2f _size;
  e_panel _id; ///< entry identifier
};

#endif /* !PANELELEMENT_HH_ */
