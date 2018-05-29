#include <tools/OptionsParser.hh>

#include <iomanip>
#include <iostream>
#include <algorithm>

#include <debug/Debug.hh>



OptionsParser::OptionsParser(int ac, const char** av)
{
  // Build a copy of the forwarded argument vector
  for (int i = 0; i < ac; ++i)
  {
    _av.push_back(av[i]);
  }

  // Expecting at least the program name; The arguments count must be consistent
  auto nb_args(_av.size());
  if (!nb_args || static_cast<int> (nb_args) != ac)
  {
    // Should never happen
    throw ArgumentsException("Ill-formed arguments list.");
  }

  // Build the supported options list
  _supportedOptions["help"] = { { "-h", "--help" }, "Show this help" };
  _supportedOptions["version"] = {
    { "-v", "--version" }, "Display " + _av[0] + " version" };

  _supportedOptions["fullscreen"] = { { "-f", "--fullscreen", "--full-screen" },
                                      "Launch the game in full screen" };

  _supportedOptions["replay"] = {
    { "-r", "--replay" }, "Replay the last replay file" };


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

  // Check the given arguments validity
  validArguments();
}


void OptionsParser::displayVersion() const noexcept
{
  std::cout << _av[0] << ": version ";

  // Print the version numbers, each number separated by a dot
  std::cout << *(_version.begin());
  for (auto it = _version.begin() + 1; it != _version.end(); ++it)
  {
    std::cout << '.' << *it;
  }

  std::cout << std::endl;
}


void OptionsParser::displayHelp() const noexcept
{
  displayVersion();
  std::cout << '\n'
            << "Usage:" << '\n';

  std::vector<std::string> lines;
  for (const auto& opt: _supportedOptions)
  {
    std::string line = "\n ";
    for (const auto& str: opt.second.first)
    {
      line.append(" ");
      line.append(str);
      if (str == "")
      {
        line.append("  ");
      }
    }

    lines.push_back(line);
  }

  // Get the longest line in order to align correctly the descriptions
  auto max_length = 0ul;
  for (const auto str: lines)
  {
    max_length = std::max(max_length, str.length());
  }

  auto i = 0;
  for (const auto& opt: _supportedOptions)
  {
    auto line = lines[i++];
    std::cout << line
              << std::setfill(' ')
              << std::setw(static_cast<int> (max_length - line.length() + 1))
              << " "
              << opt.second.second;
  }

  std::cout << '\n' << std::endl;


  std::cout << max_length << std::endl;
}




/// \todo refactor the options list (or at least the search)
void OptionsParser::validArguments() const
{
  bool invalid_args = false;

  // For each argument, check if it matches any option
  // +1: skip program name
  for (auto arg = _av.begin() + 1; arg != _av.end(); ++arg)
  {
    // Search the argument in the supported options list
    bool arg_valid = false;
    for (const auto& opt: _supportedOptions)
    {
      if (std::find(opt.second.first.begin(), opt.second.first.end(), *arg)
          != opt.second.first.end())
      {
        arg_valid = true;
        break;
      }
    }

    if (!arg_valid)
    {
      ERROR("Invalid argument", *arg);
      invalid_args = true;
    }
  }

  if (invalid_args)
  {
    displayHelp();
    throw ArgumentsException();
  }
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
