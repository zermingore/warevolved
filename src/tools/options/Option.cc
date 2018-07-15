/**
 * \file
 * \date July 14, 2018
 * \author Zermingore
 * \brief Option class implementation
 */

#include <tools/options/Option.hh>


Option::Option(const std::string name,
               const std::string description,
               const std::vector<std::string> aliases,
               const e_option_argument required_arguments)
  : _name(name)
  , _description(description)
  , _aliases(aliases)
  , _requiredArgs(required_arguments)
  , _provided(false)
{
}
