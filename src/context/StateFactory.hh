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


/**
 * \class StateFactory
 * \brief Creates States according to the factory design pattern
 */
class StateFactory
{
public:
  /**
   * \brief Returns the State matching the given State identifier
   *   Aborts the execution if no State is found given this identifier
   * \param state: The state identifier
   * \return A pointer to the matching State
   */
  static std::shared_ptr<State> createState(const e_state& state);
};


#endif /* !STATE_FACTORY_HH_ */
