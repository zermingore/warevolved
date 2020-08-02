/**
 * \file
 * \date July 7, 2017
 * \author Zermingore
 * \brief OptionsParser class definition
 */

#include <tools/options/OptionsParser.hh>

#include <algorithm>
#include <iomanip>
#include <iostream>

#include <debug/Debug.hh>
#include <tools/options/Option.hh>



OptionsParser::OptionsParser(int ac, const char** av)
{
  // Build a copy of the forwarded argument vector
  for (int i = 0; i < ac; ++i)
  {
    _av.emplace_back(av[i]);
  }

  // Expecting at least the program name; The arguments count must be consistent
  const auto nb_args(_av.size());
  if ((nb_args == 0u) || static_cast<int> (nb_args) != ac)
  {
    // Should never happen
    throw ArgumentsException("Ill-formed arguments list.");
  }


  // Build the supported options list
  _supportedOptions.emplace(
    "help",
    Option("help",
           "Show this help",
           { "-h", "--help" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "version",
    Option("version",
           "Display " + _av[0] + " version",
           { "-v", "--version" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "random-seed",
    Option("random-seed",
           "Initialize the random generator with the given seed;"
           " --random-seed=123456789",
           { "", "--random-seed" },
           e_option_argument::REQUIRED
    )
  );

  _supportedOptions.emplace(
    "fullscreen",
    Option("fullscreen",
           "Launch the game in full screen",
           { "-f", "--fullscreen", "--full-screen" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "replay",
    Option("replay",
           "Replay the last replay file",
           { "-r", "--replay" },
           e_option_argument::NONE
    )
  );

  _supportedOptions.emplace(
    "replay-file",
    Option("replay-file",
           "Replay file (recording or playing); --replay-file=example",
           { "", "--replay-file" },
           e_option_argument::REQUIRED
    )
  );

  _supportedOptions.emplace(
    "load-map",
    Option("load-map",
           "Load the Map from the given file; --load-map=my_map",
           { "", "--load-map" },
           e_option_argument::REQUIRED
    )
  );

  _supportedOptions.emplace(
    "saves-directory",
    Option("saves-directory",
           "Save games directory; --saves-directory=~/.we/saves/",
           { "", "--saves-directory" },
           e_option_argument::REQUIRED
    )
  );

  _supportedOptions.emplace(
    "edit-map",
    Option("edit-map",
           "Edit or create the given map; --edit-map=~/.we/map/map.xml/",
           { "", "--edit-map" },
           e_option_argument::REQUIRED
    )
  );
}



std::optional<const Option>
OptionsParser::operator[] (const std::string& name) const noexcept(true)
{
  const auto opt = _supportedOptions.at(name);
  if (opt.provided())
  {
    return opt;
  }

  return {};
}



void OptionsParser::parse()
{
  // Check the given arguments validity
  validArguments();

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


  for (const auto& [name, opt]: _supportedOptions)
  {
    std::string line = "\n ";
    for (const auto& str: opt.aliases())
    {
      line.append(" ");
      line.append(str);
      if (str.empty())
      {
        line.append("  ");
      }
    }

    lines.emplace_back(line);
  }

  // Get the longest line in order to align correctly the descriptions
  auto max_length = 0ul;
  for (const auto& str: lines)
  {
    max_length = std::max(max_length, str.length());
  }

  // Print the descriptions
  auto i = 0u;
  for (const auto& [name, opt]: _supportedOptions)
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



void OptionsParser::validArguments()
{
  std::string error_msg; // Append any error to this variable

  // For each command line argument, check if it matches any option
  // +1: skip program name
  for (auto option = _av.begin() + 1; option != _av.end(); ++option)
  {
    // Extract any argument associated to the current option
    std::string argument;
    std::string op = *option;
    if (auto pos = option->find('='); pos != std::string::npos)
    {
      argument = option->substr(pos + 1);
      op = option->substr(0, pos);
      std::cout << "opt " << op << ": args: " << argument << '\n';
    }

    // Search the provided option in the supported options list
    bool opt_valid = false;
    for (auto& [name, opt]: _supportedOptions)
    {
      auto flags = opt.aliases();
      if (std::find(flags.begin(), flags.end(), op) != flags.end())
      {
        opt.setProvided();
        opt.populateArguments(argument);
        opt_valid = true;
        if (opt.requiredArguments() == e_option_argument::REQUIRED)
        {
          if (argument.length() == 0u)
          {
            error_msg.append("\tOption " + op + " missing argument\n");
          }
        }
      }
    }

    if (!opt_valid)
    {
      error_msg.append("\tUnsupported option: " + op + '\n');
    }
  }

  if (!error_msg.empty())
  {
    displayHelp();
    throw ArgumentsException(error_msg);
  }
}



bool OptionsParser::optionExists(const std::string& option) const
{
  // Find the considered option in _supportedOptions ("help" for instance)
  for (const auto& [name, opt]: _supportedOptions)
  {
    if (opt.name() == option)
    {
      return opt.provided();
    }
  }

  // We should always find a given option
  ERROR("[IMPLEMENTATION ERROR] Unknown option", option);
  std::exit(1);
}
