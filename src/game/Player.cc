#include <game/Player.hh>
#include <common/globals.hh>


Player::Player() :
  _isDead (false)
{
  static unsigned int static_id = 0;
  _index = static_id++;
}

Player::~Player()
{
  for (auto it: _units)
    delete it;
}

Coords Player::getLastCursorPosition() {
  return _lastCursorPosition;
}

Color Player::getCursorColor() {
  return _cursorColor;
}

Color Player::getUnitsColor() {
  return _unitsColor;
}

void Player::setCursorColor(Color color) {
  _cursorColor = color;
}

void Player::setUnitsColor(Color color) {
  _unitsColor = color;
}

void Player::saveCursorPosition() {
  _lastCursorPosition = CURSOR->getCoords();
}

void Player::addUnit(Unit &unit)
{
  // _units.insert(_id++, &unit);
  _units.push_back(&unit);
}

Unit &Player::newUnit(e_units unit, unsigned int line, unsigned int column)
{
  Unit *new_unit;

  switch (unit)
  {
    case E_UNITS_SOLDIERS:
      new_unit = new Unit("soldiers");
      break;

    default:
      DEBUG_PRINT("Unable to match this unit type");
      break;
  }

  new_unit->setCellCoordinates(line, column);
  new_unit->setPlayerId(_index);
  _units.push_back(new_unit);

  return *new_unit;
}