#include <common/Text.hh>
#include <common/enums/ranks.hh>
#include <common/enums/terrains.hh>

Text::Text(unsigned int language) :
  _language (language)
{
}

Text::~Text() {
}


std::string Text::getRankName(e_rank rank) {
  return _ranks[rank];
}


//template <typename T>
//std::string Text::getName(T id)
//{
//  if (typeid (id) == typeid (e_rank))
//    return "_ranks[static_cast <unsigned int> (id)]";
//}

//template <e_rank>
std::string Text::getName(e_rank rank)
{
  if (rank == 1) // TODO tmp test (need a DB)
    return "PRIVATE";
  return "Fetch error";
}

std::string Text::getName(e_terrain terrain)
{
  if (terrain == 1) // TODO tmp test (need a DB)
    return "FOREST";
  return "Fetch error";
}
