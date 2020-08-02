/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief System class declaration
 */

#include <common/System.hh>

System::System(const unsigned int sfml_major, const unsigned int sfml_minor)
  : _sfmlMajor (sfml_major)
  , _sfmlMinor (sfml_minor)
{
}
