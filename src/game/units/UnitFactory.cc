#include <game/units/UnitFactory.hh>
#include <game/units/Unit.hh>
#include <game/units/Soldier.hh>



std::shared_ptr<Unit> UnitFactory::createUnit(const e_unit& unit)
{
  switch (unit)
  {
    case e_unit::SOLDIERS:
      return std::make_shared<Soldier> ();

    default:
      ERROR("Trying to create unit", static_cast<int> (unit));
      assert(!"Unable to create the unit with the given name");
      return nullptr;
  }
}
