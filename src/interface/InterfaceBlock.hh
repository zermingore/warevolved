#ifndef INTERFACEBLOCK_HH_
# define INTERFACEBLOCK_HH_

# include <common/include.hh>


class InterfaceBlock
{
protected:
  InterfaceBlock() {};

  /** \brief draw the interface block, at its _position
   */
  virtual void draw() = 0;

  /** \brief sets origin menu to the right cursor relative position
   */
  virtual void setOrigin() = 0;


  sf::Vector2f _origin; ///< Origin position of the menu
  Image _background; ///< background image
};

#endif /* !INTERFACEBLOCK_HH_ */
