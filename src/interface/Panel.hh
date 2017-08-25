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
# include <common/enums/panel_status.hh>

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
   * \brief Toggle the side panel status (Left, Right, Deactivated)
   */
  void toggleStatus();

  /**
   * \brief Origin setter
   * \param origin New panel origin
   */
  void setOrigin(const graphics::Pos2 origin) { _origin = origin; }

  /**
   * \brief Updates the window size
   *   Updates the Panel components size accordingly
   */
  void setWindowSize(const graphics::Size2& size);


  /**
   * \brief Update the panel before drawing
   */
  virtual void update() override final;


  /**
   * \brief Draw the components of the panel
   */
  virtual void draw() override final;


private:
  graphics::Size2 _windowSize; ///< Drawing space size

  graphics::Pos2 _origin = {0, 0}; ///< Top left or top right corner - width
  graphics::Size2 _size; ///< (A ratio of the horizontal room) x (window height)

  std::shared_ptr<resources::Image> _background; ///< Panel's background

  e_panel_status _status; ///< Position on the screen (Left, Right, Deactivated)
};


} // namespace interface

#endif /* !PANEL_HH_ */
