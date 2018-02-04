/**
 * \file
 * \date Jan 11, 2015
 * \author Zermingore
 */

#ifndef INTERFACE_ELEMENT_HH_
# define INTERFACE_ELEMENT_HH_

# include <string>
# include <memory>

# include <structures/Vector.hh>
# include <graphics/graphic_types.hh>
# include <interface/InterfaceSettings.hh>
# include <game/Map.hh>
# include <resources/ResourcesManager.hh>

namespace graphics {
  class Sprite;
}


namespace interface {

/**
 * \class InterfaceElement
 * \brief Represents an element of the interface (cursor, menu entry, ...).
 * \note Abstract class
 */
class InterfaceElement
{
public:
  /**
   * \brief Deleted default constructor as we need an image
   */
  InterfaceElement() = delete;

  /**
   * \brief constructor. Initialize position, scale and rotation of the element.
   * \param image_string name of the Image resource
   */
  explicit InterfaceElement(const std::string& image_name);

  /// Default destructor
  virtual ~InterfaceElement() = default;


  /**
   * \brief image name getter.
   * \return name of the image resource.
   */
  auto name() const { return _imgName; }

  /**
   * \brief position getter.
   * \return Position of the element in the absolute frame.
   */
  auto position() const { return _position; }

  /**
   * \brief _coords getter
   * \return _coords value in the grid frame
   */
  auto coords() const { return _coords; }

  /**
   * \brief scale getter.
   * \return scale of the element, related to cells size.
   */
  auto scale() const { return _scale; }

  /**
   * \brief rotation getter.
   * \return Rotation of the element in grid frame.
   */
  auto rotation() const { return _rotation; }

  /**
   * \brief position setter.
   * \param position cells coordinates to place the element.
   */
  void setCoords(const Coords& coords) { _coords = coords; }

  /**
   * \brief position setter.
   * \param position cells coordinates to place the element.
   */
  void setPosition(const graphics::Pos2& position) { _position = position; }

  /**
   * \brief scale setter.
   * \param scale_x scale in x related to cells size.
   * \param scale_y scale in y related to cells size.
   */
  void setScale(const float scale_x, const float scale_y) {
    _scale.x = scale_x;
    _scale.y = scale_y;
  }

  /**
   * \brief scale setter.
   * \param scale scale to apply in x and y related to cells size.
   */
  void setScale(const float scale) { setScale(scale, scale); }

  /**
   * \brief rotation setter.
   *
   * The rotation angle is given in degrees.
   * The given rotation angle is related to the corner of the sprite.
   * The GraphicsEngine is in charge of the translation to have a rotation
   * related to che center of the sprite.
   *
   * \param rotation angle of the rotation.
   */
  void setRotation(const float rotation) { _rotation = rotation; }


  /**
   * \brief Updates the graphical attributes of the elements before rendering
   */
  virtual void update() = 0;


  /**
   * \brief Default InterfaceElement draw method.
   * \note Calls the GraphicsEngine::draw() method with the sprite of _image
   */

  virtual void draw() = 0;



protected:
  std::string _imgName;                      ///< Associated image name
  std::shared_ptr<graphics::Sprite> _sprite; ///< Associated sprite

  graphics::Pos2 _position; ///< Element position (in pixels)
  Coords _coords;           ///< Position (in cells; not always filled)
  graphics::Scale2 _scale;  ///< Element scale (related to a Cell size)
  float _rotation;          ///< Element rotation
};


} // namespace interface



#endif /* !INTERFACE_ELEMENT_HH_ */
