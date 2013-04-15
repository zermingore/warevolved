#ifndef SETTINGS_HH_
# define SETTINGS_HH_

class Settings
{
public:
  /// Ctor - Dtor
  Settings();
  Settings(unsigned int depth,
		   unsigned int stencil,
		   unsigned int antialiasing);

  ~Settings();

  /// SFML settings getters
  unsigned int getDepth();
  unsigned int getStencil();
  unsigned int getAntialiasing();

  bool getFullscreen();


  /// SFML settings setters
  void setDepth(unsigned int depth);
  void setStencil(unsigned int stencil);
  void setAntialiasing(unsigned int antialiasing);

  /// generic settings
  void setFullscreen(bool fullscreen);


private:
  /// SFML settings
  unsigned int _depth;
  unsigned int _stencil;
  unsigned int _antialiasing;

  /// generic settings
  bool _fullscreen;
};

#endif /* !SETTINGS_HH_ */
