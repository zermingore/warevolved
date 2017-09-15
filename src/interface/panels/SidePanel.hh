#ifndef SIDEPANEL_HH_
# define SIDEPANEL_HH_

# include <interface/panels/Panel.hh>
# include <interface/panels/PanelElement.hh>


class SidePanel: public Panel
{
public:
  SidePanel();
  void draw();
};

#endif /* !SIDEPANEL_HH_ */
