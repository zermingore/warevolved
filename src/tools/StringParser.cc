/**
 * \file
 * \date April 20, 2017
 * \author Zermingore
 * \brief StringParser class definition
 */

#include <regex>

#include <tools/StringParser.hh>


std::vector<std::string> StringParser::split(const std::string& input,
                                             const std::string& regex)
{
  // passing -1 as the submatch index parameter performs splitting
  std::regex re(regex);
  std::sregex_token_iterator first{input.begin(), input.end(), re, -1};
  std::sregex_token_iterator last;

  return {first, last};
}
