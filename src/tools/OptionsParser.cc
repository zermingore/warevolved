#include <tools/OptionsParser.hh>

#include <iostream>
#include <algorithm>


OptionsParser::OptionsParser(int ac, const char** av)
{
  for (int i = 0; i < ac; ++i)
  {
    _av.push_back(av[i]);
  }
}


void OptionsParser::displayVersion() const
{
  std::cout << _av[0] << ": version " << _version << std::endl;
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


bool OptionsParser::optionExists(std::string& option) const
{
  return std::find(_av.begin(), _av.end(), option) != _av.end();
}
