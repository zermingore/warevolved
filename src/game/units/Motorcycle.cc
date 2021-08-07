/**
 * \file
 * \date March 20, 2020
 * \author Zermingore
 * \brief Motorcycle (specific Unit) class definition
 */

#include <game/units/Motorcycle.hh>

#include <debug/Debug.hh>
#include <game/units/UnitsFactory.hh>
#include <graphics/Sprite.hh>
#include <graphics/Properties.hh>
#include <resources/ResourcesManager.hh>



Motorcycle::Motorcycle()
  : Vehicle()
{
  _type = e_unit::MOTORCYCLE;
  _allowedCrewTypes = { {e_unit::SOLDIER, true} };

  /// \todo Multiple sprites
  _sprite = std::make_shared<graphics::Sprite> ("motorcycle");

  _motionValue = 5;
  _maxHp = UnitsFactory::typeMaxHp(_type);
  _hp = _maxHp;
  _attackValue = 0;

  _minRange = 0;
  _maxRange = 0;

  _maxCrewMembers = 1;

  /// \todo Initialize the map
  // The keys should stay constant; only the values are adjusted
  // _crew[e_unit_role::DRIVER] = nullptr;
}



bool Motorcycle::canOpenFire() const
{
  return !_crew.empty();
}



bool Motorcycle::addToCrew(std::shared_ptr<Unit> unit, e_unit_role role)
{
  if (_crew.size() >= _maxCrewMembers)
  {
    ERROR("Called 'addToCrew()' with a full Vehicle");
    return false;
  }

  if (role != e_unit_role::DRIVER && role != e_unit_role::NONE)
  {
    ERROR("Motorcycle do not handle role:", debug::e_unit_role_string(role));
    return false;
  }

  std::shared_ptr<Unit> driver = nullptr;
  std::shared_ptr<Unit> copilot = nullptr;


  auto it = std::find_if(
    _crew.begin(),
    _crew.end(),
    [=] (std::pair<e_unit_role, std::shared_ptr<Unit>> member) -> bool {
      return member.first == e_unit_role::DRIVER;
    }
  );

  if (it == _crew.end())
  {
    _crew.push_back({e_unit_role::DRIVER, unit});
    updateSprite();
    return true;
  }

  ERROR("[IMPLEMENTATION ERROR] Failed trying to add the unit to the crew");
  return false;
}



void Motorcycle::updateSprite()
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


  // Draw the motorcycle itself at the beginning (under its crew)
  sf::Sprite sprite(*resources::ResourcesManager::getTexture("motorcycle"));
  render.draw(sprite);

  for (const auto& member: _crew)
  {
    std::string texture;
    switch (member.first)
    {
      case e_unit_role::DRIVER:
        texture = "motorcycle_driver";
        break;

      case e_unit_role::PASSENGER:
        texture = "motorcycle_passenger";
        break;

      default:
        ERROR("Unexpected role in a motorcycle: ",
              static_cast<int> (member.first));
        break;
    }

    sf::Sprite crewSprite(*resources::ResourcesManager::getTexture(texture));

    // Add the passenger to the render texture
    sprite.setPosition(0, 0);
    render.draw(crewSprite);
  }

  render.display();
  _sprite->setTexture(render.getTexture());
}