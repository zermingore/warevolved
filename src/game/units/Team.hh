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

/** \class Units group
 *
 */
class Team
{
public:
  /** \brief Constructor
   ** builds a new team with \param unit and \param unit2
   */
  Team(Unit *unit, Unit *unit2);

  /// \brief Destructor
  ~Team();

  /** \brief _members getter
   ** \return _members: every members of the team
   */
  std::vector<Unit*> *getMembers();

  /** \brief adds a member to the Team
   ** \param Unit
   */
  void addMember(Unit *unit);

private:
  std::vector<Unit*> *_members; ///< list of all team members
};

#endif /* !TEAM_HH_ */
