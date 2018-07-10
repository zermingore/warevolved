/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief Tool to parse options (from the command line),
 *   including the associated exceptions definitions
 */

#ifndef OPTIONS_PARSER_HH_
# define OPTIONS_PARSER_HH_

# include <map>
# include <vector>
# include <utility>
# include <string>
# include <exception>


/**
 * \enum e_option_argument
 * \brief Provides flags if an argument is expected, optional, ...
 * \note For instance the --replay-file option expects a replay file
 */
enum class e_option_argument
{
  NONE = 0,
  OPTIONAL,
  REQUIRED,
};


/**
 * \class ArgumentsException
 * \brief Exception thrown if the provided are invalid
 */
class ArgumentsException: public std::exception
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
  explicit ArgumentsException(const std::string msg)
    : _exc(msg)
  {
  }

  /**
   * \brief Standard exception what() override
   *   Displays the provided error message through the constructor
   */
  const char *what() const noexcept override { return _exc.c_str(); }

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
   * \param option Check the existence of this option
   * \note Skip the first element of the argument vector (the program name)
   * \return true if the option exists
   */
  bool optionExists(const std::string option);

  /// Options list type:
  /// list["help"] = {
  ///                  { "-h", "--help" },
  ///                  "display help",
  ///                  e_option_argument::NONE
  ///                }
  using options_list =
    std::map<std::string, std::tuple<std::vector<std::string>,
                                     std::string,
                                     e_option_argument>>;
  /// \note could add a callback in the options_list
  ///   (maybe use a class instead of map['help'] = { {-h}, "show help", f })


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
   * \todo support options with arguments (--replay filename)
   * \note throws if at least one argument is invalid
   */
  void validArguments() const;


  std::vector<std::string> _av; ///< mapping of the C arguments vector

  /// Game's version (major, minor, bugfix)
  const std::vector<size_t> _version = {0, 1, 0};

  /// List of supported options (map["help"] = {"-h", "--help"})
  options_list _supportedOptions;
};

#endif /* !OPTIONS_PARSER_HH_ */
