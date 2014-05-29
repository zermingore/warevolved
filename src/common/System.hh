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

  unsigned int sfmlMajor();
  unsigned int sfmlMinor();

private:
  unsigned int _sfmlMajor; ///< SFML major version (x.*)
  unsigned int _sfmlMinor; ///< SFML minor version (*.x)
};

#endif /* !COMMON_HH_ */
