/**
 * \file
 * \date July 14, 2018
 * \author Zermingore
 * \brief Option class implementation
 */

#include <debug/Debug.hh>
#include <tools/options/Option.hh>
#include <utility>


Option::Option(std::string  name,
               std::string  description,
               std::vector<std::string>  aliases,
               const e_option_argument required_arguments)
  : _name(std::move(name))
  , _description(std::move(description))
  , _aliases(std::move(aliases))
  , _requiredArgs(required_arguments)
  , _provided(false)
{
}


void Option::populateArguments(const std::string& arguments)
{
  auto end_arg = arguments.find(',');
  decltype(end_arg) begin_arg = 0;
  auto args = arguments;
  while (end_arg != std::string::npos)
  {
    // Extract the current argument
    _arguments.emplace_back(args.substr(0, end_arg));

    // Omit the begining of the arguments string
    begin_arg = end_arg + 1;
    args = args.substr(begin_arg);
    end_arg = args.find(',');
  }

  // Handle last argument
  _arguments.emplace_back(args);


  // Debug: Options + arguments print
  // NOTICE("Option", _name, "arguments: ");
  // for (const auto& arg: _arguments)
  // {
  //   std::cout << arg << " ";
  // }
  // std::cout << '\n';
}
