#ifndef INTERFACEELEMENT_HH_
# define INTERFACEELEMENT_HH_

/**
 * \file InterfaceElement definition
 */

# include <string>
# include <common/using.hh>
# include <common/structures/Vector.hh>


class InterfaceElement
{
public:
  /**
   * \brief Default constructor.
   *
   * Initializes position, scale and rotation of the element.
   *
   * \param image_string name of the Image resource
   */
  explicit InterfaceElement(const std::string& image_name);


  //  virtual void onSelection();

  // ___________________________ Getters / Setters _________________________ //
  /**
   * \brief image name getter.
   * \return name of the image resource.
   */
  std::string name() const { return _img_name; }

  /**
   * \brief position getter.
   * \return Position of the element in grid frame.
   */
  Coords position() const { return _position; }

  /**
   * \brief scale getter.
   * \return scale of the element, related to cells size.
   */
  Vector2<float> scale() const { return _scale; }

  /**
   * \brief rotation getter.
   * \return Rotation of the element in grid frame.
   */
  float rotation() const { return _rotation; }


  /**
   * \brief position setter.
   * \param position cells coordinates to place the element.
   */
  void setPosition(const Coords &position) {
    _position = position;
  }

  /**
   * \brief scale setter.
   * \param scale_x scale in x related to cells size.
   * \param scale_y scale in y related to cells size.
   */
  void setScale(const float &scale_x, const float &scale_y)
  {
    _scale.x = scale_x;
    _scale.y = scale_y;
  }

  /**
   * \brief scale setter.
   * \param scale scale to apply in x and y related to cells size.
   */
  void setScale(const float &scale) { setScale(scale, scale); }

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
  void setRotation(const float &rotation) { _rotation = rotation; }

protected:
  std::string _img_name; ///< Associated image name

  Coords _position;      ///< Element position
  Vector2<float> _scale; ///< Element scale (related to a Cell size)
  float _rotation;       ///< Element rotation
};

// InterfaceElementButton
//# include <resources/Font.hh>
//std::string _backgroundName; ///< background image name
//std::shared_ptr<sf::Text> _label; ///< label text
//Font _font; ///< label font

#endif /* !INTERFACEELEMENT_HH_ */
