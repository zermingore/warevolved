/**
 * \file
 * \date March 4, 2013
 * \author Zermingore
 * \brief Handle the Frame Per Second computation
 */

#ifndef TOOLS_FPS_HH_
# define TOOLS_FPS_HH_

# include <array>
# include <chrono>


/**
 * \class Fps
 * \brief Store the time to draw the last frames and compute the resulting FPS
 * \note If the compilation flag DEBUG_PERFS is not set,
 *   the frame rate will be limited to 60
 *   it will be unlimited otherwise
 */
class Fps
{
public:
  /**
   * \brief update the frames computation time history
   * \return the average fps (based on the kept history)
   * \note During the first 128 frames creation, the returned fps value is wrong
   */
  static double updateFps(double last_frame_duration);


private:
  enum { _nbFrames = 128 }; ///< Nb frames kept
  /// Storing only a few frames in a ring buffer
  static std::array<double, _nbFrames> _lastFramesDuration;


  static bool _firstBurst;           ///< Initialization
  static double _computationTimeSum; ///< Cached sum
  static size_t _currentIndex;       ///< Frame array index
};

#endif /* !TOOLS_FPS_HH_ */
