#ifndef TERRAINS_HH_
# define TERRAINS_HH_

# include <string>

// TODO move in Terain.hh class file
/** \brief listing of all terrains
 */
enum e_terrains
{
  E_TERRAINS_FOREST = 0,

  E_TERRAINS_NB_TERRAINS,
  E_TERRAINS_NONE
};

// array which contents all terrains file names (filled by the GraphicEngine)
extern std::string g_terrains_name[E_TERRAINS_NB_TERRAINS];

#endif /* !TERRAINS_HH_ */
