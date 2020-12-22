/**
 * \file
 * \date July 14, 2018
 * \author Zermingore
 * \brief Option class declaration, representing command line options
 */

#ifndef TOOLS_OPTIONS_OPTION_HH_
# define TOOLS_OPTIONS_OPTION_HH_

# include <vector>
# include <string>


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
 * \class Option
 * \brief Represent command line options
 */
class Option
{
public:
  /**
   * \brief Deleted default constructor: Options attributes required
   */
  Option() = delete;

  /**
   * \brief Constructor
   * \param name Option name (used in the code)
   * \param description Option description to print in the help message
   * \param aliases Command line option invocation names
   * \param required_arguments Are arguments optional mandatory or forbidden ?
   */
  Option(std::string name,
         std::string description,
         std::vector<std::string> aliases,
         const e_option_argument required_arguments);

  /**
   * \brief _provided getter
   */
  auto provided() const { return _provided; }

  /**
   * \brief Sets the provided boolean to true
   * \note _provided is set to false in the constructor
   */
  void setProvided() { _provided = true; }

  /**
   * \brief Full option name getter ("help" for instance)
   * \return Option handy name
   */
  auto name() const { return _name; }

  /**
   * \brief Command line aliases getter
   * \return Option aliases list
   */
  auto aliases() const { return _aliases; }

  /**
   * \brief Description getter
   * \return Option description
   */
  auto description() const { return _description; }

  /**
   * \brief Argument status getter
   * \return Wether the option expects an argument
   */
  auto requiredArguments() const { return _requiredArgs; }

  /**
   * \brief Arguments getter
   * \return Option's arguments list
   */
  auto arguments() const { return _arguments; }

  /**
   * \brief Append the given arguments to the arguments list
   * \note Split the arguments using the ',' delimiter
   */
  void populateArguments(const std::string& arguments);


private:
  const std::string _name; ///< Option handy name
  const std::string _description; ///< Option description, used in help
  const std::vector<std::string> _aliases; ///< Command line invocations
  const e_option_argument _requiredArgs; ///< Does the option takes arguments
  std::vector<std::string> _arguments; ///< Option arguments (--opt=arg1,arg2)
  bool _provided; ///< Was the option provided on the command line
};

#endif /* !TOOLS_OPTIONS_OPTION_HH_ */
