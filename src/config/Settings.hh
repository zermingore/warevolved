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
 *   program options
 */
class Settings
{
public:
  /**
   * \brief graphic depth getter.
   * \return depth value.
   */
  auto depth() { return _depth; }

  /**
   * \brief graphic stencil getter.
   * \return stencil value.
   */
  auto stencil() { return _stencil; }

  /**
   * \brief Anti aliasing getter.
   * \return Anti aliasing coefficient.
   */
  auto antiAliasing() { return _antiAliasing; }

  /**
   * \brief _fullScreen getter.
   * \return true if we're in full screen false otherwise.
   */
  auto fullScreen() { return _fullScreen; }

  /**
   * \brief _keyRepeatDelay getter.
   * \return the required time to consider a "second pressure" (in ms).
   */
  auto keyRepeatDelay() { return _keyRepeatDelay; }

  /**
   * \brief _keyRepeatDelay setter.
   * \param delay delay to consider a key as maintained, in ms
   */
  void setKeyRepeatDelay(const size_t delay) { _keyRepeatDelay = delay; }


  /**
   * \brief Sets the _fullScreen attribute
   * Adjust the concerned graphical attributes accordingly
   */
  void setFullScreen(const bool fullScreen);



private:
  /**
   * \brief Sets graphic attributes
   * It is called when the fullscreen parameter is changed
   * \param depth graphic depth value
   * \param stencil stencil value
   * \param antiAliasing anti aliasing coefficient
   */
  void setGraphics(const unsigned int depth,
                   const unsigned int stencil,
                   const unsigned int antiAliasing);


  // graphic settings
  unsigned int _depth; ///< Depth buffer size.
  unsigned int _stencil; ///< Stencil buffer size
  unsigned int _antiAliasing; ///< Anti aliasing level.

  // generic settings
  bool _fullScreen; ///< Notify if we're running in full screen.

  ///< Required time to consider a "second pressure" in ms.
  size_t _keyRepeatDelay;
};


#endif /* !SETTINGS_HH_ */