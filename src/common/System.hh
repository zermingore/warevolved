/*
 * common/System.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef SYSTEM_HH_
# define SYSTEM_HH_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

/** \class System storage class
 ** designed to fill bugs reports
 ** keeps software information
 **  - SFML version
 ** keeps hardware information
 */

class System
{
public:
  /** \brief Default Constructor
   */
  System() = delete;
  System(unsigned int sfml_major, unsigned int sfml_minor);

  inline void setSfmlMajor(unsigned int major) { _sfmlMajor = major; }
  inline void setSfmlMinor(unsigned int minor) { _sfmlMinor = minor; }

  inline unsigned int sfmlMajor() { return _sfmlMajor; }
  inline unsigned int sfmlMinor() { return _sfmlMinor; }

private:
  unsigned int _sfmlMajor; ///< SFML major version (x.*)
  unsigned int _sfmlMinor; ///< SFML minor version (*.x)
};

#endif /* !SYSTEM_HH_ */
