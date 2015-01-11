#ifndef PANEL_HH_
# define PANEL_HH_

# include <interface/InterfaceBlock.hh>
# include <interface/panels/PanelElement.hh>


class Panel : InterfaceBlock
{
public:
  Panel();
  void draw();
  void setOrigin();


private:
  std::vector<PanelElement> _elts; ///< panel's elements
  sf::Vector2f _origin; ///< Origin position of the menu
};

#endif /* !PANEL_HH_ */
