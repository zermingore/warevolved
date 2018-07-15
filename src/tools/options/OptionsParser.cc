#include <tools/options/OptionsParser.hh>

#include <iomanip>
#include <iostream>
#include <algorithm>

#include <tools/options/Option.hh>
#include <debug/Debug.hh>



OptionsParser::OptionsParser(int ac, const char** av)
{
  // Build a copy of the forwarded argument vector
  for (int i = 0; i < ac; ++i)
  {
    _av.push_back(av[i]);
  }

  // Expecting at least the program name; The arguments count must be consistent
  const auto nb_args(_av.size());
  if (!nb_args || static_cast<int> (nb_args) != ac)
  {
    // Should never happen
    throw ArgumentsException("Ill-formed arguments list.");
  }


  // Build the supported options list
  _supportedOptions.emplace_back(
    Option("help",
           "Show this help",
           { "-h", "--help" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace_back(
    Option("version",
           "Display " + _av[0] + " version",
           { "-v", "--version" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace_back(
    Option("fullscreen",
           "Launch the game in full screen",
           { "-f", "--fullscreen", "--full-screen" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace_back(
    Option("replay",
           "Replay the last replay file",
           { "-r", "--replay" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace_back(
    Option("replay-file",
           "Replay file (recording or playing)",
           { "", "--replay-file" },
           e_option_argument::REQUIRED
    )
  );
}



void OptionsParser::parse()
{
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
    for (const auto& str: opt.aliases())
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
              << opt.description();
  }

  std::cout << '\n' << std::endl;
}



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
      auto flags = opt.aliases();
      if (std::find(flags.begin(), flags.end(), op) != flags.end())
      {
        opt_valid = true;
        if (opt.requiredArguments() == e_option_argument::REQUIRED)
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



bool OptionsParser::optionExists(const std::string option) const
{
  // Find the considered option in _supportedOptions ("help" for instance)
  for (const auto& opt: _supportedOptions)
  {
    if (opt.name() == option)
    {
      // Checks if one of its argument was provided (ex: "-h" or "--help")
      for (const auto& opt_alias: opt.aliases())
      {
        // _av.begin() + 1: Skip the first element (program name)
        if (std::find(_av.begin() + 1, _av.end(), opt_alias) != _av.end())
        {
          return true;
        }
      }

      return false;
    }
  }

  // We should always find a given option
  ERROR("[IMPLEMENTATION ERROR] Unknown option", option);
  std::exit(1);

  return false;
}
