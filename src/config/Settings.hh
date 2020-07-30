/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Global settings class declaration.
 */

#ifndef SETTINGS_HH_
# define SETTINGS_HH_



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
   * \brief Default constructor
   */
  Settings() = default;

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
   * \brief Sets the _fullScreen attribute
   * Adjust the concerned graphical attributes accordingly
   */
  void setFullScreen(bool fullScreen);



private:
  /**
   * \brief Sets graphic attributes. Called on fullscreen parameter change
   * \param depth graphic depth value
   * \param stencil stencil value
   * \param antiAliasing anti aliasing coefficient
   */
  void setGraphics(unsigned int depth,
                   unsigned int stencil,
                   unsigned int antiAliasing);


  // graphic settings
  unsigned int _depth = 0;        ///< Depth buffer size
  unsigned int _stencil = 0;      ///< Stencil buffer size
  unsigned int _antiAliasing = 0; ///< Anti aliasing level

  // generic settings
  bool _fullScreen = false; ///< Notify if we're running in full screen
};


#endif /* !SETTINGS_HH_ */
