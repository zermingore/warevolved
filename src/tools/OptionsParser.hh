/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief Tool to parse options (from the command line)
 */

#ifndef OPTIONS_PARSER_HH_
# define OPTIONS_PARSER_HH_

# include <map>
# include <vector>

/// The options prefix as a constant to handle Windows options, one day
const char OPTIONS_PREFIX = '-';


/**
 * \class OptionsParser
 * \brief Parses the command line arguments
 * \note Options must be preceded by a OPTIONS_DELIMITER
 */
class OptionsParser
{
public:
  /**
   * \brief Disabled default constructor as the argument vector is required
   */
  OptionsParser() = delete;

  /**
   * \brief Default destructor
   */
  ~OptionsParser() = default;

  /**
   * \brief Disabled copy constructor.
   *   There's (apparently) no good reason to need it
   */
  OptionsParser(const OptionsParser&) = delete;

  /**
   * \brief Constructor.
   *   Builds the iterable vector of options from the command line options
   * \param ac Argument count
   * \param av Argument vector (C-style)
   * \warning The provided argument vector must contain (at least) ac entries
   * \note This parameters should be directly forwarded from the main
   * \note Throw if the arguments are invalid
   */
  OptionsParser(int ac, const char** av);


  /**
   * \brief Outputs the game's version
   */
  void displayVersion() const;

  /**
   * \brief Outputs the usage message
   */
  void displayHelp() const;

  /**
   * \brief Check the existence of a given option
   * \param option Check the existence of this option
   * \return \true if the option exists
   */
  bool optionExists(std::string& option) const;



private:
  std::vector<std::string> _av; ///< mapping of the C arguments vector

  /// Options with arguments map[option] == {arguments list}
  std::map<std::string, std::vector<std::string>> _options;

  std::string _version; ///< Game's version
};

#endif /* !OPTIONS_PARSER_HH_ */
