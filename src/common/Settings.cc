#include <common/Settings.hh>
#include <common/constants.hh>


Settings::Settings(unsigned int depth,
                   unsigned int stencil,
                   unsigned int antiAliasing) :
  _depth (depth),
  _stencil (stencil),
  _antiAliasing (antiAliasing),
  _fullScreen (false),
  _keyRepeatDelay(0)
{
}

unsigned int Settings::getDepth() {
  return _depth;
}

unsigned int Settings::getStencil() {
  return _stencil;
}

unsigned int Settings::getAntiAliasing() {
  return _antiAliasing;
}

bool Settings::getFullScreen() {
  return _fullScreen;
}

int Settings::getKeyRepeatDelay() {
  return _keyRepeatDelay;
}


void Settings::setDepth(unsigned int depth) {
  _depth = depth;
}

void Settings::setStencil(unsigned int stencil) {
  _stencil = stencil;
}

void Settings::setAntiAliasing(unsigned int antiAliasing) {
  _antiAliasing = antiAliasing;
}

void Settings::setFullScreen(bool fullScreen) {
  _fullScreen = fullScreen;
}

void Settings::setKeyRepeatDelay(int key_repeat_delay) {
  _keyRepeatDelay = key_repeat_delay;
}
