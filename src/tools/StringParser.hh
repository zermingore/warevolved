/**
 * \file
 * \date April 20, 2017
 * \author Zermingore
 * \brief StringParser helper class declaration
 */

#ifndef STRING_PARSER_HH_
# define STRING_PARSER_HH_

# include <string>
# include <vector>


/**
 * \class StringParser
 * \brief Split the given string in tokens according to the given regexp
 * \note Static class
 */
class StringParser
{
public:
  /**
   * \brief Split a string into tokens, according to the given regexp
   * \param input String to parse
   * \param regex Split according to this regexp
   * \return The split string as a list of tokens
   * \note the regexp is not part of the tokens
   */
  static std::vector<std::string> split(const std::string& input,
                                        const std::string& regex);
};


#endif /* !STRING_PARSER_HH_ */
