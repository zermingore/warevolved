#include <game/units/Team.hh>


Team::Team(std::shared_ptr<Unit> unit, std::shared_ptr<Unit> unit2)
{
  _members.push_back(unit);
  _members.push_back(unit2);
}
