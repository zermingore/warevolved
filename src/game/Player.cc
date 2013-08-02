#include <game/Player.hh>
#include <common/globals.hh>


Player::Player() {
  // Fully transparent cursor color (=> original sprite color)
}

Player::~Player() {
}


void Player::init() {
  g_status->addPlayer(this);
}

Coords Player::getLastCursorPosition() {
  return _lastCursorPosition;
}

Color Player::getCursorColor() {
  return _cursorColor;
}

void Player::setCursorColor(Color color) {
  _cursorColor = color;
}

void Player::saveCursorPosition() {
  _lastCursorPosition = CURSOR->getCoords();
}
