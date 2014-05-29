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
  /** \brief Constructor
   ** sets graphic attributes
   ** \param depth graphic depth value
   ** \param stencil stencil value
   ** \param antiAliasing anti aliasing coefficient
   */
  Settings(unsigned int depth,
           unsigned int stencil,
           unsigned int antiAliasing);

  /** \brief graphic depth getter
   ** \return depth value
   */
  inline unsigned int depth() { return _depth; }

  /** \brief graphic getter
   ** \return stencil value
   */
  inline unsigned int stencil() { return _stencil; }

  /** \brief anti aliasing getter
   ** \return anti aliasing coefficient
   */
  inline unsigned int antiAliasing() { return _antiAliasing; }

  /** \brief _fullScreen getter
   ** \return true if we're in full screen
   **   false otherwise
   */
  inline bool fullScreen() { return _fullScreen; }

  /** \brief _keyRepeatDelay getter
   ** \return the required time to consider a "second pressure" (in ms)
   */
  inline int keyRepeatDelay() { return _keyRepeatDelay; }

  /** \brief _keyRepeatDelay setter
   */
  inline void setKeyRepeatDelay(int delay) { _keyRepeatDelay = delay; }

  // graphics settings setters
  inline void setDepth(unsigned int depth) { _depth = depth; }
  inline void setStencil(unsigned int stencil) { _stencil = stencil; }
  inline void setAntiAliasing(unsigned int aa) { _antiAliasing = aa; }

  // generic settings
  inline void setFullScreen(bool fullScreen) { _fullScreen = fullScreen; }


private:
  // graphic settings
  unsigned int _depth; ///< depth buffer size
  unsigned int _stencil; ///< stencil buffer size
  unsigned int _antiAliasing; ///< anti aliasing level

  // generic settings
  bool _fullScreen; ///< notify if we're running in full screen

  int _keyRepeatDelay; ///< required time to consider a "second pressure"
                       ///< in ms, must be positive to avoid locking keyboard
};

#endif /* !SETTINGS_HH_ */
