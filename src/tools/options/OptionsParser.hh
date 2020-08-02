/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief Tool to parse options (from the command line),
 *   including the associated exceptions definitions
 */

#ifndef TOOLS_OPTIONS_OPTIONS_PARSER_HH_
# define TOOLS_OPTIONS_OPTIONS_PARSER_HH_

# include <map>
# include <vector>
# include <utility>
# include <string>
# include <exception>
# include <optional>

# include <tools/options/Option.hh>


/**
 * \class ArgumentsException
 * \brief Exception thrown if the provided are invalid
 */
class ArgumentsException final: public std::exception
{
public:
  /**
   * \brief Default constructor
   */
  ArgumentsException() = default;

  /**
   * \brief Constructor, initializing the exception message
   * \param msg Exception message (returned by exc.what())
   */
  explicit ArgumentsException(const std::string& msg)
    : _exc(msg)
  {
  }

  /**
   * \brief Standard exception what() override
   *   Displays the provided error message through the constructor
   */
  const char *what() const noexcept override final { return _exc.c_str(); }

private:
  /// Error message displayed by exc.what()
  std::string _exc = "Arguments exception";
};


/**
 * \class ArgumentsHelpVersionException
 * \brief Exception thrown if help or version argument were given
 */
class ArgumentsHelpVersionException: public std::exception
{
};



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
   * \warning The argument vector must contain ac entries (throws otherwise)
   * \note This parameters should be directly forwarded from the main
   * \note Throws if no arguments is provided
   */
  OptionsParser(int ac, const char** av);


  /**
   * \brief Parse the options list, checking the arguments validity
   * \note Throws if the help or version is requested (-h --help -v --version)
   * \note Throws if the arguments are invalid (unrecognized option)
   */
  void parse();

  /**
   * \brief Check the existence of a given option
   * \param option Check if this specific option was provided
   * \warning Aborts the execution if the provided option is not referenced
   * \return true if the option was provided, false otherwise
   */
  bool optionExists(const std::string& option) const;

  /**
   * \brief Retrieve a given Option, by its name
   * \param name Option name to retrieve
   * \note throws std::out_of_range if the given option does not exist
   * \return The associated option, if any
   */
  // std::optional<const std::vector<std::string>>
  std::optional<const Option>
  operator[] (const std::string& name) const noexcept(true);


private:
  /**
   * \brief Outputs the game's version
   */
  void displayVersion() const noexcept;

  /**
   * \brief Outputs the usage message
   */
  void displayHelp() const noexcept;

  /**
   * \brief Test the provided arguments validity
   *   Check if the arguments match supported options
   * \todo support store replay file name arguments
   * \note throws if at least one argument is invalid
   * \note throws if the help or version option is provided
   */
  void validArguments();


  std::vector<std::string> _av; ///< mapping of the C arguments vector

  /// Game's version (major, minor, bugfix)
  const std::vector<size_t> _version = {0, 1, 0};

  /// List of supported options
  std::map<std::string, Option> _supportedOptions;
};


#endif /* !TOOLS_OPTIONS_OPTIONS_PARSER_HH_ */
