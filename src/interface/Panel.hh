/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class declaration
 */


#ifndef PANEL_HH_
# define PANEL_HH_

# include <graphics/graphic_types.hh>
# include <interface/InterfaceElement.hh>


namespace resources {
  class Image;
}


namespace interface {


/**
 * \class Panel
 * \brief Side panel class,
 *   where the minimap and hovered cell data are displayed
 */
class Panel: public InterfaceElement
{
public:
  /**
   * \brief Default constructor: call InterfaceElement constructor
   */
  Panel();

  /**
   * \brief Defaulted destructor
   */
  ~Panel() = default;


  /**
   * \brief Origin setter
   * \param origin New panel origin
   */
  void setOrigin(const graphics::Pos2 origin) { _origin = origin; }


  virtual void update() override final;


  /**
   * \brief Draw the components of the panel
   */
  virtual void draw() override final;


private:
  ///< Panel's image origin: top left or top right corner
  graphics::Pos2 _origin = {0, 0};

  ///< (A ratio of the horizontal space) x (window height)
  graphics::Size2 _size;

  std::shared_ptr<resources::Image> _background; ///< Panel's background

  ///< Image containing the panel elements
  std::shared_ptr<resources::Image> _image;
};


} // namespace interface

#endif /* !PANEL_HH_ */
