/*
 * common/Settings.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef SETTINGS_HH_
# define SETTINGS_HH_

# include <string>


// TODO create subclasses: VideoSettings, GameSettings

/** \brief Settings in a class designed to store
 **   user's preferences
 **   system's informations (such as video modes)
 */
class Settings
{
public:
  /** \brief initialization function, sets graphic attributes
   ** \param depth graphic depth value
   ** \param stencil stencil value
   ** \param antiAliasing anti aliasing coefficient
   */
  static void initialize(unsigned int depth,
                         unsigned int stencil,
                         unsigned int antiAliasing);

  /** \brief graphic depth getter
   ** \return depth value
   */
  static unsigned int depth() { return Settings::_depth; }

  /** \brief graphic getter
   ** \return stencil value
   */
  static unsigned int stencil() { return Settings::_stencil; }

  /** \brief anti aliasing getter
   ** \return anti aliasing coefficient
   */
  static unsigned int antiAliasing() { return Settings::_antiAliasing; }

  /** \brief _fullScreen getter
   ** \return true if we're in full screen
   **   false otherwise
   */
  static bool fullScreen() { return Settings::_fullScreen; }

  /** \brief _keyRepeatDelay getter
   ** \return the required time to consider a "second pressure" (in ms)
   */
  static int keyRepeatDelay() { return Settings::_keyRepeatDelay; }

  /** \brief _keyRepeatDelay setter
   */
  static void setKeyRepeatDelay(int delay) { Settings::_keyRepeatDelay = delay; }

  // graphics settings setters
  static void setDepth(unsigned int depth) { Settings::_depth = depth; }
  static void setStencil(unsigned int stencil) { Settings::_stencil = stencil; }
  static void setAntiAliasing(unsigned int aa) { Settings::_antiAliasing = aa; }

  // generic settings
  static void setFullScreen(bool fullScreen) { Settings::_fullScreen = fullScreen; }


private:
  // graphic settings
  static unsigned int _depth; ///< depth buffer size
  static unsigned int _stencil; ///< stencil buffer size
  static unsigned int _antiAliasing; ///< anti aliasing level

  // generic settings
  static bool _fullScreen; ///< notify if we're running in full screen

  static unsigned int _keyRepeatDelay; ///< required time to consider a "second pressure"
                                       ///< in ms, must be positive to avoid locking keyboard
};

#endif /* !SETTINGS_HH_ */
