#ifndef STRING_PARSER_HH_
# define STRING_PARSER_HH_

# include <string>
# include <vector>


class StringParser
{
public:
  /**
   * \brief Parse a given string into tokens, according to the given regexp
   * \param input String to parse
   * \param regex Split according to this regexp
   * \return The input string split with regexp
   */
  static std::vector<std::string> split(const std::string& input,
                                        const std::string& regex);
};


#endif /* !STRING_PARSER_HH_ */
