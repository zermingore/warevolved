#ifndef TERRAINS_HH_
# define TERRAINS_HH_

# include <string>

/** \brief listing of all terrains
 */
enum e_terrains
{
  E_FOREST = 0,

  E_NB_TERRAINS,
  E_TERRAIN_NONE
};

// array which contents all terrains file names (filled by the GraphicEngine)
extern std::string g_filenames_terrains[E_NB_TERRAINS];

#endif /* !TERRAINS_HH_ */
