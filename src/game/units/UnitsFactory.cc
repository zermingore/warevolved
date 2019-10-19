/**
 * \file
 * \date February 9, 2017
 * \author Zermingore
 * \brief UnitsFactory class definition: build Units
 */

#include <game/units/UnitsFactory.hh>

#include <debug/Debug.hh>
#include <game/units/Unit.hh>

#include <game/units/Soldier.hh>
#include <game/units/Car.hh>



std::unique_ptr<Unit> UnitsFactory::createUnit(const e_unit& unit)
{
  switch (unit)
  {
    case e_unit::SOLDIER:
      return std::make_unique<Soldier> ();

    case e_unit::CAR:
      return std::make_unique<Car> ();

    default:
      ERROR("Tried to create unit", static_cast<int> (unit));
      assert(false && "Unable to create the given unit");
      return nullptr;
  }
}



int UnitsFactory::typeMaxHp(const e_unit& type)
{
  switch (type)
  {
    case e_unit::SOLDIER:
      return 10;

    case e_unit::CAR:
      return 30;

    default:
      ERROR("Failed getting max hp for Unit type", static_cast<int> (type));
      assert(false && "Unit type not found");
      return -1;
  }
}