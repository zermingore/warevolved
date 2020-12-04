/**
 * \file
 * \date Jul 23, 2013
 * \author Zermingore
 * \brief Debugging macros and Debug class declaration
 */

#ifndef DEBUG_HH_
# define DEBUG_HH_

# include <memory>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cassert> // not needed here, just for modules including this file
# include <iomanip>
# include <map>

# include <generated/enum_print/enum_print.hh>



// Log file name
# ifdef __unix__
#   define LOG_FILENAME "LOG"
#   define LOG_FILENAME_OLD "LOG_old"
# else
#   define LOG_FILENAME "LOG.txt"
#   define LOG_FILENAME_OLD "LOG_old.txt"
# endif

// Print colors
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

// Messages specific colors
# define COLOR_ERROR   COLOR_RED
# define COLOR_WARNING COLOR_YELLOW
# define COLOR_SUCCESS COLOR_GREEN
# define COLOR_VERBOSE COLOR_BLUE
# define COLOR_NOTICE  COLOR_CYAN


/**
 * \def DEBUG_PRINT(x) debug print macro
 * Prints the given string only if compiled with the DEBUG flag
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

# ifdef DEBUG
#   define PRINTF Debug::printf
# else
#   define PRINTF Debug::logPrintf
# endif

# define PRINT_ONCE Debug::printOnce



/**
 * \class Debug
 * \brief Regroups handy methods to help debugging (print, log)
 */
class Debug
{
public:
  /**
   * \brief Move the eventualy existing log file; Create the new one
   */
  static void init();

  /**
   * \brief Print the given arguments in the log and, on debug, print on stdout
   * \param head First parameter
   * \param tail Rest of the parameters, if any
   * \note Templated
   */
  template<typename T, typename... Tail>
  static void constexpr logPrintf(const T head, const Tail... tail);

  /**
   * \brief Print the given element into the log file
   * \param head element to print in the log
   * \note head must override the << stream operator
   */
  template<typename T>
  static constexpr void printLog(const T head);

  /**
   * \brief print as error given parameters on standard output
   * \param head element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void constexpr error(const T head, const Tail... tail);

  /**
   * \brief print as error given parameters on standard output
   * \param head element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void constexpr notice(const T head, const Tail... tail);

  /**
   * \brief print as error given parameters on standard output
   * \param head element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void constexpr warning(const T head, const Tail... tail);

  /**
   * \brief print given parameters on standard output
   * \param head element to print right now
   * \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void constexpr printf(const T head, const Tail... tail);

  /**
   * \brief print one unique time the given string
   * \param str string to print once
   * \warning The unicity check relies on the given string
   */
  static void printOnce(const std::string& str);

  /**
   * \brief Set the current thread name
   * \param name Name of the thread
   * \warning System dependent; Unix only
   */
  static void setThisThreadName(const std::string& name);



private:
  /**
   * \brief Prints every argument to the console and to the log
   * \param head First argument
   * \param tail Eventual following arguments
   */
  template<typename T, typename... Tail>
  static void constexpr bodylogprintf(const T head, const Tail... tail);

  /**
   * \brief Prints the current time to the log
   */
  static void logTime();


  static std::unique_ptr<std::ofstream> _log; ///< log file

  /// Track already displayed strings
  static std::map<std::string, bool> _printedOnce;
};


# include <debug/Debug.hxx>

#endif /* !DEBUG_HH_ */
