/**
 * \file
 * \date October 16, 2016
 * \author Zermingore
 */

#ifndef STATE_FACTORY_HH_
# define STATE_FACTORY_HH_

# include <memory>
# include <context/State.hh>
# include <common/enums/states.hh>


class StateFactory
{
public:
  static std::shared_ptr<State> createState(e_state& state);
};


#endif /* !STATE_FACTORY_HH_ */
