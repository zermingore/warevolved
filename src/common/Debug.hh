/*
 * common/Debug.hh
 *
 *  Created on: Jul 23, 2013
 *      Author: Zermingore
 */

#ifndef DEBUG_HH_
# define DEBUG_HH_

# include <iostream>
# include <fstream>
# include <sstream>

/// \def Log file name
# ifdef __unix__
#   define LOG_FILENAME "LOG"
#   define LOG_FILENAME_OLD "/tmp/LOG_war_evolved"
# else
#   define LOG_FILENAME "LOG.txt"
#   define LOG_FILENAME_OLD "LOG_old.txt"
# endif


/** \macro debug print macro
 ** prints the given string
 **   only if we compiled with the DEBUG flag
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
#   define DEBUG_PRINT_VALUE(x) do { \
      std::cout << #x << ": " << x << std::endl; \
    } while (0)
# else
#   define DEBUG_PRINT_VALUE(x) do { \
    } while (0)
# endif

# ifdef DEBUG
#   define PRINTF Debug::printf
# else
#   define PRINTF do { \
    } while (0)
# endif



class Debug
{
public:
  static void init();

  /** \brief adds the string message to the log file
   ** \param msg message to append
   ** \param err true if the message should be printed as an error
   ** NOTE: reopens the file each time we add a message (slow)
   */
  static void log(const std::string &msg, char severity = ' ');

  template<typename T, typename... Tail>
  static void logPrintf(T head, Tail... tail)
  {
	time_t now = time(0);
	struct tm *full_date = localtime(&now);
	char buf[80] = {0};
    std::ofstream log(LOG_FILENAME, std::ios_base::out | std::ios_base::app);

	strftime(buf, 80, "%Y-%m-%d @ %T", full_date); // building date
	log << buf << "\t";
	bodylogprintf(head, tail...);
  }

  template<typename T, typename... Tail>
  static void bodylogprintf(T head, Tail... tail)
  {
	print(head);
	bodylogprintf(tail...);
  }

  // execute after the last argument
  static void bodylogprintf()
  {
	std::ofstream log(LOG_FILENAME, std::ios_base::out | std::ios_base::app);
	log << std::endl;
	std::cout << std::endl;
  }

  template<typename T>
  static void print(T head)
  {
	std::ofstream log(LOG_FILENAME, std::ios_base::out | std::ios_base::app);
	log << " " << head;
	std::cout << head << " ";
  }


  /** \brief print given parameters on standard output
   ** \param head: element to print right now
   ** \param tail eventually, rest of given arguments list
   */
  template<typename T, typename... Tail>
  static void printf(T head, Tail... tail)
  {
	std::cout << head << " ";
	printf(tail...);
  }

  /** \brief appends a new line after last parameter
   */
  static void printf()
  {
	std::cout << std::endl;
  }
};


#endif /* !DEBUG_HH_ */
