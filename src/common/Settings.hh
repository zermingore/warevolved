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
  unsigned int getDepth();

  /** \brief graphic getter
   ** \return stencil value
   */
  unsigned int getStencil();

  /** \brief anti aliasing getter
   ** \return anti aliasing coefficient
   */
  unsigned int getAntiAliasing();

  /** \brief _fullScreen getter
   ** \return true if we're in full screen
   **   false otherwise
   */
  bool getFullScreen();

  /** \brief _keyRepeatDelay getter
   ** \return the required time to consider a "second pressure" (in ms)
   */
  int getKeyRepeatDelay();

  /** \brief _keyRepeatDelay setter
   */
  void setKeyRepeatDelay(int key_repeat_delay);


  // SFML settings setters
  void setDepth(unsigned int depth);
  void setStencil(unsigned int stencil);
  void setAntiAliasing(unsigned int antiAliasing);

  // generic settings
  void setFullScreen(bool fullScreen);


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
