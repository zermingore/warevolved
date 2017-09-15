/**
 * \file
 * \date Jul 23, 2013
 * \author Zermingore
 */

#ifndef DEBUG_HH_
# define DEBUG_HH_

# include <memory>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cassert> // not needed here, just for modules including this file


/// \def Log file name
# ifdef __unix__
#   define LOG_FILENAME "LOG"
#   define LOG_FILENAME_OLD "/tmp/LOG_war_evolved"
# else
#   define LOG_FILENAME "LOG.txt"
#   define LOG_FILENAME_OLD "LOG_old.txt"
# endif

/// \def Print colors
# ifdef __unix__
#   define COLOR_NORMAL  "\x1B[0m"
#   define COLOR_RED     "\x1B[31m"
#   define COLOR_GREEN   "\x1B[32m"
#   define COLOR_YELLOW  "\x1B[33m"
#   define COLOR_BLUE    "\x1B[34m"
#   define COLOR_MAGENTA "\x1B[35m"
#   define COLOR_CYAN    "\x1B[36m"
#   define COLOR_WHITE   "\x1B[37m"
# else
#   define COLOR_NORMAL  ""
#   define COLOR_RED     ""
#   define COLOR_GREEN   ""
#   define COLOR_YELLOW  ""
#   define COLOR_BLUE    ""
#   define COLOR_MAGENTA ""
#   define COLOR_CYAN    ""
#   define COLOR_WHITE   ""
# endif

/// \def Messages specific colors
# define COLOR_ERROR   COLOR_RED
# define COLOR_WARNING COLOR_YELLOW
# define COLOR_SUCCESS COLOR_GREEN
# define COLOR_VERBOSE COLOR_BLUE
# define COLOR_NOTICE  COLOR_CYAN


/**
 * \macro debug print macro
 * prints the given string
 *   only if we compiled with the DEBUG flag
 */
# ifdef DEBUG
#   define DEBUG_PRINT(x) do { \
      std::cout << x << std::endl; \
    } while (0)
# else
#   define DEBUG_PRINT(x) do { \
    } while (0)
# endif


# ifdef DEBUG
#   define PRINT_VALUE(x) do { \
      std::cout << #x << ": " << x << std::endl; \
    } while (0)
# else
#   define PRINT_VALUE(x) do { \
    } while (0)
# endif


# define ERROR   Debug::error
# define NOTICE  Debug::notice
# define WARNING Debug::warning

/// \todo in release, printf should print in a log
# ifdef DEBUG
#   define PRINTF Debug::printf
# else
#   define PRINTF do { \
    } while (0);
# endif



/**
 * \class Debug
 * \brief Regroups handy methods to help debugging (print, log)
 */
class Debug
{
public:
  template<typename T, typename... Tail>
  static void logPrintf(const T head, const Tail... tail)
  {
    std::ofstream log(LOG_FILENAME, std::ios_base::out | std::ios_base::app);

	time_t now = time(nullptr);
	struct tm *full_date = localtime(&now);
	char buf[80] = {0};

	strftime(buf, 80, "%Y-%m-%d @ %T", full_date); // building date
	log << buf << "\t";
	bodylogprintf(head, tail...);
    printf(head, tail...);
  }

  /**
   * \brief Print the given element into the log file
   * \parm head element to print in the log
   * \note head must override the << stream operator
   */
  template<typename T>
  static void printLog(const T head)
  {
    *_log << " " << head;
  }


  /**
   * \brief print as error given parameters on standard output
   * \param head: element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void error(const T head, const Tail... tail)
  {
    time_t now = time(nullptr);
	struct tm *full_date = localtime(&now);
	char buf[80] = {0};

	strftime(buf, 80, "%Y-%m-%d @ %T", full_date); // building date
	*_log << buf << "\t";
	bodylogprintf(head, tail...);

	std::cout << COLOR_ERROR;
	printf(head, tail...);
  }

  /**
   * \brief print as error given parameters on standard output
   * \param head: element to print right now
   * \param tail eventually, rest of given arguments list
   * \todo log notices and warnings
   */
  template<typename T, typename... Tail>
  static void notice(const T head, const Tail... tail)
  {
	std::cout << COLOR_NOTICE;
	printf(head, tail...);
  }

  /**
   * \brief print as error given parameters on standard output
   * \param head: element to print right now
   * \param tail eventually, rest of given arguments list
   * \todo log notices and warnings
   */
  template<typename T, typename... Tail>
  static void warning(const T head, const Tail... tail)
  {
	std::cout << COLOR_WARNING;
	printf(head, tail...);
  }

  /**
   * \brief print given parameters on standard output
   * \param head: element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void printf(const T head, const Tail... tail)
  {
	std::cout << head << " ";
	printf(tail...);
  }


private:
  /**
   * \brief prints every argument to the console and to the log
   * \param head First argument
   * \param tail Eventual following arguments
   */
  template<typename T, typename... Tail>
  static void bodylogprintf(const T head, const Tail... tail)
  {
	printLog(head);
	bodylogprintf(tail...);
  }

  /// Execute after the last argument
  static void bodylogprintf();

  /// appends a new line after last parameter
  static void printf();


  static std::unique_ptr<std::ofstream> _log; ///< log file
};


#endif /* !DEBUG_HH_ */
