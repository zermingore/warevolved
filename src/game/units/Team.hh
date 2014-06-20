/*
 * game/units/Team.hh/Team.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef TEAM_HH_
# define TEAM_HH_

class Unit;

# include <game/units/Unit.hh>

/** \class Team: Units group
 */
class Team
{
public:
  /** \brief Constructor
   ** builds a new team with \param unit and \param unit2
   */
  Team(std::shared_ptr<Unit> unit, std::shared_ptr<Unit> unit2);

  /** \brief _members getter
   ** \return _members: every members of the team
   */
  inline std::vector<std::shared_ptr<Unit>> members() { return _members; }

  /** \brief adds a member to the Team
   ** \param Unit
   */
  inline void addMember(std::shared_ptr<Unit> unit) { _members.push_back(unit); }

private:
  std::vector<std::shared_ptr<Unit>> _members; ///< list of all team members
};

#endif /* !TEAM_HH_ */
