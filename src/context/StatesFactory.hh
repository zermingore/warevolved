/**
 * \file
 * \date October 16, 2016
 * \author Zermingore
 * \brief StatesFactory class declaration
 */

#ifndef STATE_FACTORY_HH_
# define STATE_FACTORY_HH_

# include <memory>
# include <context/State.hh>


/**
 * \class StatesFactory
 * \brief Creates States according to the factory design pattern
 */
class StatesFactory
{
public:
  /**
   * \brief Returns the State matching the given State identifier
   *   Aborts the execution if no State is found given this identifier
   * \param state The state identifier
   * \return A pointer to the matching State
   */
  static std::unique_ptr<State> createState(const e_state& state);
};


#endif /* !STATE_FACTORY_HH_ */
