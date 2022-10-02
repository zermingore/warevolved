#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <tools/options/OptionsParser.hh>



TEST_CASE("Arguments")
{
  SUBCASE("help")
  {
    const char* argv[2] = { "prog_name", "--help" };
    OptionsParser opt{2, argv};
    try
    {
      opt.parse();
    }
    catch (const ArgumentsHelpVersionException&)
    {
      // Expecting an "arguments help version exception"
    }
  }

  SUBCASE("version")
  {
    const char* argv[2] = { "prog_name", "--version" };
    OptionsParser opt{2, argv};
    try
    {
      opt.parse();
    }
    catch (const ArgumentsHelpVersionException&)
    {
      // Expecting an "arguments help version exception"
    }
  }

  SUBCASE("Invalid argument")
  {
    const char* argv[2] = { "prog_name", "--lol" };
    OptionsParser opt{2, argv};
    try
    {
      opt.parse();
    }
    catch (const ArgumentsException&)
    {
      // Expecting an "arguments exception"
    }
  }

  SUBCASE("No argument")
  {
    const char* argv[1] = { "prog_name" };
    OptionsParser opt{1, argv};
    opt.parse();
  }
}
