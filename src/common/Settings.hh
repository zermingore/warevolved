#ifndef SETTINGS_HH_
# define SETTINGS_HH_

# include <string>

/** \brief Settings in a class designed to store
 **   user's preferences
 **   system's informations (such as video modes)
 */


// TODO create subclasses: VideoSettings, GameSettings

class Settings
{
public:
  /** \brief Default Constructor
   */
  Settings();
  Settings(unsigned int depth,
		   unsigned int stencil,
		   unsigned int antiAliasing);

  /** \brief Default Destructor
   */
  ~Settings();


  /// SFML settings getters
  unsigned int getDepth();
  unsigned int getStencil();
  unsigned int getAntiAliasing();

  bool getFullScreen();

  /** \brief returns cursor's file name
   **   (with complete path and extension)
   **
   ** \return cursor file name in use
   */
  const std::string getCursorFileName();


  /// SFML settings setters
  void setDepth(unsigned int depth);
  void setStencil(unsigned int stencil);
  void setAntiAliasing(unsigned int antiAliasing);

  /// generic settings
  void setFullScreen(bool fullScreen);


private:
  /// SFML settings
  unsigned int _depth; ///< depth buffer size
  unsigned int _stencil; ///< stencil buffer size
  unsigned int _antiAliasing; ///< anti aliasing level

  /// generic settings
  bool _fullScreen; ///< notify if we're running in full screen

public:
  std::string _cursorFileName; ///< cursor's sprite file name
};

#endif /* !SETTINGS_HH_ */
