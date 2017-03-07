/**
 * \file
 * \date August 4, 2013
 * \author Zermingore
 */

#ifndef APPLICATION_HH_
# define APPLICATION_HH_


/**
 * \class Application
 * \brief An application is a full screen state
 *   it could be the Main Menu, a Battle, ...
 */
class Application
{
public:
  virtual ~Application() {}

  virtual void buildMap() = 0; /// \todo should not be in the abstract class
};

#endif /* !APPLICATION_HH_ */
