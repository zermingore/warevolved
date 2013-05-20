#ifndef COMMON_HH_
# define COMMON_HH_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

/** \brief System storage class
 ** designed to fill bugs reports
 ** keeps software information
 **  - SFML version
 ** keeps hardware informations
 */

class System
{
public:
  /** \brief Default Constructor
   */
  System();
  System(unsigned int sfml_major, unsigned int sfml_minor);

  /** \brief Destructor
   */
  ~System();

  void setSfmlMajor(unsigned int sfml_major);
  void setSfmlMinor(unsigned int sfml_minor);

  unsigned int getSfmlMajor();
  unsigned int getSfmlMinor();

private:
  unsigned int _sfmlMajor; ///< SFML major version (x.*)
  unsigned int _sfmlMinor; ///< SFML minor version (*.x)
};

#endif /* !COMMON_HH_ */
