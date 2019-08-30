/**
 * \file
 * \date February 9, 2017
 * \author Zermingore
 * \brief UnitFactory class definition: build Units
 */

#include <game/units/UnitFactory.hh>

#include <debug/Debug.hh>
#include <game/units/Unit.hh>

#include <game/units/Soldier.hh>
#include <game/units/Car.hh>



std::unique_ptr<Unit> UnitFactory::createUnit(const e_unit& unit)
{
  switch (unit)
  {
    case e_unit::SOLDIERS:
      return std::make_unique<Soldier> ();

    case e_unit::CAR:
      return std::make_unique<Car> ();

    default:
      ERROR("Tried to create unit", static_cast<int> (unit));
      assert(false && "Unable to create the given unit");
      return nullptr;
  }
}
