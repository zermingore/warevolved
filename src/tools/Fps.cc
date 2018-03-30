#include <tools/Fps.hh>
#include <debug/OSD.hh>

#include <cmath>
#include <iostream>


namespace tools {

// Static attributes definition
std::array<double, Fps::_nbFrames> Fps::_lastFramesDuration = {};
double Fps::_computationTimeSum = 0;
size_t Fps::_currentIndex = 0;
bool Fps::_firstBurst = true;
double Fps::_fps = 0;


void Fps::updateFps(double last_frame_duration)
{
  // init: accumulating every element until the array is full
  if (_firstBurst)
  {
    _lastFramesDuration[_currentIndex] = last_frame_duration;
    _computationTimeSum += last_frame_duration;

    if (++_currentIndex % _nbFrames == _nbFrames - 1)
    {
      _firstBurst = false;
    }

    // Explicit cast to size_t
    _fps = static_cast<double> (_currentIndex) / _computationTimeSum;
    debug::OSD::addPod(_fps, "FPS");

    return;
  }


  _computationTimeSum -= _lastFramesDuration[_currentIndex];
  _lastFramesDuration[_currentIndex] = last_frame_duration;
  _computationTimeSum += last_frame_duration;

  _currentIndex = (_currentIndex + 1) % _nbFrames;

  // Explicit cast to size_t
  _fps = static_cast<double> (_nbFrames) / _computationTimeSum;
  debug::OSD::addPod(_fps, "FPS");
}


} // namespace tools
