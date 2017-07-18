#include <tools/OptionsParser.hh>

#include <iostream>
#include <algorithm>


OptionsParser::OptionsParser(int ac, const char** av)
{
  // Build a copy of the forwarded argument vector
  for (int i = 0; i < ac; ++i)
  {
    _av.push_back(av[i]);
  }

  auto nb_args(_av.size());
  if (!nb_args || static_cast<int> (nb_args) != ac)
  {
    /// \todo own exception invalid arg
    throw std::logic_error("opus"); // Invalid arguments (expecting at least the program name)
  }

  // Build the supported options list
  _supportedOptions["help"] = { { "-h", "--help" }, "show this help" };
  _supportedOptions["version"] = {
    { "-v", "--version" }, "display " + _av[0] + " version" };


  // Fetch help or version option
  if (optionExists("help"))
  {
    displayHelp();
    throw ArgumentsHelpVersionException();
  }
  if (optionExists("version"))
  {
    displayVersion();
    throw ArgumentsHelpVersionException();
  }


  /// \todo For given options, check if they exist and their argument
}


void OptionsParser::displayVersion() const
{
  std::cout << _av[0] << ": version " << _version << '\n' << std::endl;
}


void OptionsParser::displayHelp() const
{
  displayVersion();
  std::cout << '\n'
            << "Usage:" << '\n'
            << "\n  " << "-h --help    " << "display this help"
            << "\n  " << "-v --version " << "display War Evolved version"
            << '\n' << std::endl;
}


bool OptionsParser::optionExists(const std::string option)
{
  // Try to find the option string, for each possibility in _supportedOptions
  //   ex: try to match "-h" or "--help" for the "help" option
  for (auto& opt_str: _supportedOptions[option].first)
  {
    // _av.begin() + 1: Skip the first element (program name)
    if (std::find(_av.begin() + 1, _av.end(), opt_str) != _av.end())
    {
      return true;
    }
  }

  return false;
}
