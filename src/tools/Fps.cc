/**
 * \file
 * \date March 4, 2013
 * \author Zermingore
 * \namespace tools
 * \brief Fps class implementation
 */

#include <debug/OSD.hh>
#include <tools/Fps.hh>

#include <cmath>
#include <iostream>


namespace tools {


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

    _fps = static_cast<double> (_currentIndex) / _computationTimeSum;
    debug::OSD::addPod(_fps, "FPS");

    return;
  }

  _computationTimeSum -= _lastFramesDuration[_currentIndex];
  _lastFramesDuration[_currentIndex] = last_frame_duration;
  _computationTimeSum += last_frame_duration;
  _currentIndex = (_currentIndex + 1) % _nbFrames;
  _fps = static_cast<double> (_nbFrames) / _computationTimeSum;

  debug::OSD::addPod(_fps, "FPS");
}



} // namespace tools
