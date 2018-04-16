/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 */

#ifndef SYSTEM_HH_
# define SYSTEM_HH_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

/**
 * \class System
 * \brief designed to fill bugs reports
 *
 * keeps software information
 *  - SFML version
 * keeps hardware information
 */
class System
{
public:
  /// deleted Default Constructor
  System() = delete;

  /**
   * \brief sets the SFML major and minor version numbers
   */
  System(const unsigned int sfml_major, const unsigned int sfml_minor);

  /// default destructor
  ~System() = default;


  /**
   * \brief SFML major version number getter
   * \return SFML major version number
   */
  auto sfmlMajor() { return _sfmlMajor; }

  /**
   * \brief SFML minor version number getter
   * \return SFML minor version number
   */
  auto sfmlMinor() { return _sfmlMinor; }


private:
  unsigned int _sfmlMajor; ///< SFML major version (x.*)
  unsigned int _sfmlMinor; ///< SFML minor version (*.x)
};

#endif /* !SYSTEM_HH_ */
