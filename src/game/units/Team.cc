#include <game/units/Team.hh>


Team::Team(Unit *unit, Unit *unit2)
{
  _members = new std::vector<Unit*>;
  _members->push_back(unit);
  _members->push_back(unit2);
}

Team::~Team() {
  delete _members;
}

void Team::addMember(Unit *unit) {
  _members->push_back(unit);
}
