/*
 * interface/panel/Panel.hh
 *
 *  Created on: Jan 18, 2015
 *      Author: Zermingore
 */

#ifndef PANEL_HH_
# define PANEL_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <interface/panels/PanelElement.hh>


class Panel
{
public:
  /** \brief sets Panel's origin, using \param origin
   */
  inline void setOrigin(sf::Vector2f origin) { _origin = origin; }

  /** \brief sets Panel's size, using \param size
   */
  inline void setSize(sf::Vector2f size) { _size = size; }

  ///< _size getter
  inline sf::Vector2f size() { return _size; }


protected:
  /** \brief draw the Panel, at its _position
   */
  virtual void draw() = 0;

  sf::Vector2f _origin; ///< Origin position of the menu
  sf::Vector2f _size; ///< panel's size
  std::vector<PanelElement> _elts; ///< panel's elements
  Image _background; ///< background image
};

#endif /* !PANEL_HH_ */
