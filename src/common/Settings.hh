/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Global settings class definition.
 */

#ifndef SETTINGS_HH_
# define SETTINGS_HH_

# include <stddef.h> // size_t


/// \todo create subclasses: VideoSettings, GameSettings

/**
 * \class Settings
 * \brief Class storing settings.
 *
 * Storing the following settings:
 *   user's preferences
 *   system's informations (such as video modes)
 */
class Settings
{
public:
  /**
   * \brief initialization function, sets graphic attributes
   * \param depth graphic depth value
   * \param stencil stencil value
   * \param antiAliasing anti aliasing coefficient
   */
  static void initialize(unsigned int depth,
                         unsigned int stencil,
                         unsigned int antiAliasing);


  /**
   * \brief graphic depth getter.
   * \return depth value.
   */
  static unsigned int depth() { return _depth; }

  /**
   * \brief graphic stencil getter.
   * \return stencil value.
   */
  static unsigned int stencil() { return _stencil; }

  /**
   * \brief Anti aliasing getter.
   * \return Anti aliasing coefficient.
   */
  static unsigned int antiAliasing() { return _antiAliasing; }

  /**
   * \brief _fullScreen getter.
   * \return true if we're in full screen false otherwise.
   */
  static bool fullScreen() { return _fullScreen; }

  /**
   * \brief _keyRepeatDelay getter.
   * \return the required time to consider a "second pressure" (in ms).
   */
  static int keyRepeatDelay() { return _keyRepeatDelay; }

  /**
   * \brief _keyRepeatDelay setter.
   * \param delay delay to consider a key as maintained, in ms
   */
  static void setKeyRepeatDelay(size_t delay) { _keyRepeatDelay = delay; }

  // graphics settings setters
  static void setDepth(size_t depth) { _depth = depth; }
  static void setStencil(size_t stencil) { _stencil = stencil; }
  static void setAntiAliasing(size_t aa) { _antiAliasing = aa; }

  // generic settings setters
  static void setFullScreen(bool fullScreen) { _fullScreen = fullScreen; }


private:
  // graphic settings
  static unsigned int _depth; ///< Depth buffer size.
  static unsigned int _stencil; ///< Stencil buffer size
  static unsigned int _antiAliasing; ///< Anti aliasing level.

  // generic settings
  static bool _fullScreen; ///< Notify if we're running in full screen.

  static unsigned int _keyRepeatDelay; ///< Required time to consider a "second pressure" in ms.
};


#endif /* !SETTINGS_HH_ */
