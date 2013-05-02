#ifndef UNITS_HH_
# define UNITS_HH_

# include <string>

enum e_units
{
  E_UNITS_SOLDIERS = 0,

  E_UNITS_NB_UNITS,
  E_UNITS_NONE
};


static const std::string g_units_name[E_UNITS_NB_UNITS] = {"soldiers"};

#endif /* !UNITS_HH_ */
