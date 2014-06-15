/*
 * game/Applications/Application.hh
 *
 *  Created on: August 4, 2013
 *      Author: Zermingore
 */

#ifndef APPLICATION_HH_
# define APPLICATION_HH_

# include <common/Debug.hh>

/** \class Application class
 ** An application is a full screen state
 **   it could be the Main Menu, a Battle, ...
 */
class Application
{
public:
  /** \brief Constructor
   */
  Application() { PRINTF("Application Ctor"); }

  /** \brief Destructor
   */
  virtual ~Application() { PRINTF("Application Dtor"); }

  virtual void run() = 0;

  virtual void buildMap() = 0;


protected:
  virtual void init() = 0;
};

#endif /* !APPLICATION_HH_ */
