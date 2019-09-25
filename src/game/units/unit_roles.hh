#ifndef UNIT_ROLES_HH_
# define UNIT_ROLES_HH_

# include <map>

enum class e_unit_role
{
    NONE

  , PASSENGER // eventually multiple passengers
  , DRIVER    // or pilot
  , COPILOT   // may be necessary (airplane)
  , LOADER    // ex: tank
  , GUNNER    // list (airplane)
  , MECHANIC
};


const std::map<const e_unit_role, const std::string> UNIT_ROLE_STR =
{
    { e_unit_role::NONE,      "None" }
  , { e_unit_role::PASSENGER, "Passenger" }
  , { e_unit_role::DRIVER,    "Driver" }
  , { e_unit_role::COPILOT,   "Co-Pilot" }
  , { e_unit_role::LOADER,    "Loader" }
  , { e_unit_role::GUNNER,    "Gunner" }
  , { e_unit_role::MECHANIC,  "Mechanic" }
};



#endif /* !UNIT_ROLES_HH_ */
