/*
 * game/Applications/Application.hh
 *
 *  Created on: August 4, 2013
 *      Author: Zermingore
 */

#ifndef APPLICATION_HH_
# define APPLICATION_HH_


/** \class Application class
 ** An application is a full screen state
 **   it could be the Main Menu, a Battle, ...
 */
class Application
{
public:
  virtual void buildMap() = 0;
};

#endif /* !APPLICATION_HH_ */
