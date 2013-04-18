#ifndef SETTINGS_HH_
# define SETTINGS_HH_

class Settings
{
public:
  /// Ctor - Dtor
  Settings();
  Settings(unsigned int depth,
		   unsigned int stencil,
		   unsigned int antiAliasing);

  ~Settings();

  /// SFML settings getters
  unsigned int getDepth();
  unsigned int getStencil();
  unsigned int getAntiAliasing();

  bool getFullScreen();


  /// SFML settings setters
  void setDepth(unsigned int depth);
  void setStencil(unsigned int stencil);
  void setAntiAliasing(unsigned int antiAliasing);

  /// generic settings
  void setFullScreen(bool fullScreen);


private:
  /// SFML settings
  unsigned int _depth;
  unsigned int _stencil;
  unsigned int _antiAliasing;

  /// generic settings
  bool _fullScreen;
};

#endif /* !SETTINGS_HH_ */
