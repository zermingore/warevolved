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
  _supportedOptions["help"] = {
    { "-h", "--help" },
    "Show this help",
    e_option_argument::NONE
  };

  _supportedOptions["version"] = {
    { "-v", "--version" },
    "Display " + _av[0] + " version",
    e_option_argument::NONE
  };

  _supportedOptions["fullscreen"] = {
    { "-f", "--fullscreen", "--full-screen" },
    "Launch the game in full screen",
    e_option_argument::NONE
  };

  _supportedOptions["replay"] = {
    { "-r", "--replay" },
    "Replay the last replay file",
    e_option_argument::NONE
  };

  _supportedOptions["replay-file"] = {
    { "", "--replay-file" },
    "Replay file (recording or playing)",
    e_option_argument::REQUIRED
  };


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
    for (const auto& str: std::get<0>(opt.second))
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

  // Print the descriptions
  auto i = 0;
  for (const auto& opt: _supportedOptions)
  {
    auto line = lines[i++];
    std::cout << line
              << std::setfill(' ')
              << std::setw(static_cast<int> (max_length - line.length() + 1))
              << " "
              << std::get<1>(opt.second);
  }

  std::cout << '\n' << std::endl;
}




/// \todo refactor the options list (or at least the search)
void OptionsParser::validArguments() const
{
  std::string error_msg = ""; // Append any error to this variable

  // For each command line argument, check if it matches any option
  // +1: skip program name
  for (auto option = _av.begin() + 1; option != _av.end(); ++option)
  {
    // Extract any argument associated to the current option
    std::string argument = ""; /// \todo split arguments (--opt=arg1,arg2)
    std::string op = *option;
    if (auto pos = option->find('='); pos != std::string::npos)
    {
      argument = option->substr(pos + 1);
      op = option->substr(0, pos);
      std::cout << "opt " << op << ": args: " << argument << std::endl;
    }

    // Search the provided option in the supported options list
    bool opt_valid = false;
    for (const auto& opt: _supportedOptions)
    {
      auto flags = std::get<0>(opt.second);
      if (std::find(flags.begin(), flags.end(), op) != flags.end())
      {
        opt_valid = true;
        if (std::get<2>(opt.second) == e_option_argument::REQUIRED)
        {
          if (!argument.length())
          {
            error_msg.append("\tOption " + op + " missing argument\n");
          }
        }
        break;
      }
    }

    if (!opt_valid)
    {
      error_msg.append("\tUnsupported option: " + op + '\n');
    }
  }

  if (error_msg != "")
  {
    displayHelp();
    throw ArgumentsException(error_msg);
  }
}



bool OptionsParser::optionExists(const std::string option)
{
  // Try to find the option string, for each possibility in _supportedOptions
  //   ex: try to match "-h" or "--help" for the "help" option
  for (auto& opt_str: std::get<0>(_supportedOptions[option]))
  {
    // _av.begin() + 1: Skip the first element (program name)
    if (std::find(_av.begin() + 1, _av.end(), opt_str) != _av.end())
    {
      return true;
    }
  }

  return false;
}
