/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Global Settings class declaration
 */

#ifndef SETTINGS_HH_
# define SETTINGS_HH_

# include <string>
# include <vector>


/**
 * \class Settings
 * \brief Class storing settings.
 *
 * Storing the following settings:
 *   Game version
 *   Libraries versions
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
  static auto depth() { return _depth; }

  /**
   * \brief graphic stencil getter.
   * \return stencil value.
   */
  static auto stencil() { return _stencil; }

  /**
   * \brief Anti aliasing getter.
   * \return Anti aliasing coefficient.
   */
  static auto antiAliasing() { return _antiAliasing; }

  /**
   * \brief _fullScreen getter.
   * \return true if we're in full screen false otherwise.
   */
  static auto fullScreen() { return _fullScreen; }

  /**
   * \brief Sets the _fullScreen attribute
   *   and adjust the concerned graphical attributes accordingly
   */
  static void setFullScreen(bool fullScreen);


  /**
   * \brief SFML minor version number getter
   * \return SFML minor version number
   */
  static auto version() { return _version; }

  /**
   * \brief Get the version numbers, each one separated by a dot
   * \return A string containing the version (form: Major.Minor.Patch)
   */
  static std::string versionString();

  /**
   * \brief SFML major version number getter
   * \return SFML major version number
   */
  static auto sfmlMajor() { return _sfmlMajor; }

  /**
   * \brief SFML minor version number getter
   * \return SFML minor version number
   */
  static auto sfmlMinor() { return _sfmlMinor; }


private:
  /**
   * \brief Sets graphic attributes. Called on fullscreen parameter change
   * \param depth graphic depth value
   * \param stencil stencil value
   * \param antiAliasing anti aliasing coefficient
   */
  static void setGraphics(unsigned int depth,
                          unsigned int stencil,
                          unsigned int antiAliasing)
  {
    _depth = depth;
    _stencil = stencil;
    _antiAliasing = antiAliasing;
  }


  // graphic settings
  inline static unsigned int _depth;        ///< Depth buffer size
  inline static unsigned int _stencil;      ///< Stencil buffer size
  inline static unsigned int _antiAliasing; ///< Anti aliasing level

  // generic settings
  inline static bool _fullScreen; ///< Notify if we're running in full screen

  inline static const unsigned int _sfmlMajor = 2; ///< SFML major version (x.*)
  inline static const unsigned int _sfmlMinor = 1; ///< SFML minor version (*.x)

  /// Game's version (major, minor, bugfix)
  inline static const std::vector<std::size_t> _version = {0, 1, 0};
};


#endif /* !SETTINGS_HH_ */
