/**
 * \file
 * \date August 1, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class definition
 */

#include <game/units/Car.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh>
#include <graphics/Properties.hh>
#include <game/units/UnitsFactory.hh>
#include <resources/ResourcesManager.hh>



Car::Car()
  : Vehicle()
{
  _type = e_unit::CAR;
  _allowedCrewTypes = { {e_unit::SOLDIER, true} };

  /// \todo Multiple sprites
  _sprite = std::make_shared<graphics::Sprite> ("car");

  _motionValue = 5;
  _maxHp = UnitsFactory::typeMaxHp(_type);
  _hp = _maxHp;
  _attackValue = 0;

  _minRange = 0;
  _maxRange = 0;

  _maxCrewMembers = 5;

  /// \todo Initialize the map
  // The keys should stay constant; only the values are adjusted
  // _crew[e_unit_role::DRIVER] = nullptr;
  // _crew[e_unit_role::COPILOT] = nullptr;
  // _crew[e_unit_role::PASSENGER] = nullptr;
}



bool Car::canOpenFire() const
{
  for (const auto& member: _crew)
  {
    if (member.first == e_unit_role::COPILOT)
    {
      return true;
    }
  }
  return false;
}



bool Car::addToCrew(std::shared_ptr<Unit> unit, e_unit_role role)
{
  if (_crew.size() >= _maxCrewMembers)
  {
    ERROR("Called 'addToCrew()' with a full Vehicle");
    return false;
  }


  // If the role is specified, use it
  if (role != e_unit_role::NONE)
  {
    if (   role != e_unit_role::DRIVER
        && role != e_unit_role::COPILOT
        && role != e_unit_role::PASSENGER)
    {
      ERROR("Unsupported role for a car", debug::e_unit_role_string(role));
    }

    for (const auto& member: _crew)
    {
      if (member.first == role)
      {
        if (role != e_unit_role::PASSENGER)
        {
          ERROR("Already occupied role", debug::e_unit_role_string(role));
          return false;
        }
      }
    }

    _crew.push_back({role, unit});
    updateSprite();
    return true;
  }


  auto driver_occupied{false};
  auto copilot_occupied{false};
  for (const auto& member: _crew)
  {
    if (member.first == e_unit_role::DRIVER)
    {
      driver_occupied = true;
      continue;
    }

    if (member.first == e_unit_role::COPILOT)
    {
      copilot_occupied = true;
      continue;
    }
  }

  if (!driver_occupied)
  {
    _crew.push_back({e_unit_role::DRIVER, unit});
  }
  else if (!copilot_occupied)
  {
    _crew.push_back({e_unit_role::COPILOT, unit});
  }
  else
  {
    _crew.push_back({e_unit_role::PASSENGER, unit});
  }

  updateSprite();
  return true;
}



void Car::updateSprite()
{
  using p = graphics::Properties;

  // Initialize a RenderTexture
  sf::RenderTexture render;
  if (!render.create(static_cast<uint16_t> (p::cellWidth()),
                     static_cast<uint16_t> (p::cellHeight())))
  {
    ERROR("Unable to create render texture (car crew)");
    return;
  }
  render.clear(sf::Color::Transparent);


  graphics::component offset_x{0};
  graphics::component offset_y{0};
  bool flip {false}; // vertical sprite flip

  auto passengerTexture =
    *resources::ResourcesManager::getTexture("passenger");

  const auto& carTexture =
    *resources::ResourcesManager::getTexture("car");
  const graphics::Size2& carSize {
    static_cast<graphics::component> (carTexture.getSize().x),
    static_cast<graphics::component> (carTexture.getSize().y) };
  const graphics::component offset_front {carSize.x / 8.f};
  const graphics::component offset_rear {carSize.x / 2.f - carSize.x / 16.f};
  const graphics::component offset_vert_base {carSize.y / 2.f};
  const graphics::component offset_vert_in {carSize.y / 10.f};

  bool first_passenger = true; // Differentiate both passengers
  for (const auto& member: _crew)
  {
    switch (member.first)
    {
      case e_unit_role::DRIVER:
        offset_x = offset_front;
        offset_y = offset_vert_base - offset_vert_in;
        flip = false;
        break;

      case e_unit_role::COPILOT:
        offset_x = offset_front;
        offset_y = offset_vert_base + offset_vert_in;
        flip = true;
        break;

      case e_unit_role::PASSENGER:
        if (first_passenger)
        {
          first_passenger = false;
          offset_x = offset_rear;
          offset_y = offset_vert_base + offset_vert_in;
          flip = true;
        }
        else
        {
          offset_x = offset_rear;
          offset_y = offset_vert_base - offset_vert_in;
          flip = false;
        }
        break;

      default:
        ERROR("Unexpected role in a car: ", static_cast<int> (member.first));
        break;
    }

    // Add the passenger to the render texture
    sf::Sprite passengerSprite{passengerTexture};
    if (flip)
    {
      passengerSprite.setScale(1.0f, -1.0f);
    }

    passengerSprite.setPosition(offset_x, offset_y);
    render.draw(passengerSprite);
  }

  // Draw the car itself at last (over the passengers)
  sf::Sprite sprite(*resources::ResourcesManager::getTexture("car"));
  render.draw(sprite);

  render.display();
  _sprite->setTexture(render.getTexture());
}
