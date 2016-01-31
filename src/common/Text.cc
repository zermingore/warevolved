#include <common/Text.hh>
#include <common/enums/ranks.hh>
#include <common/enums/terrains.hh>

Text::Text(unsigned int language) :
  _language (language),
  _names {"John Doe", "Jack Sheppard", "James Williams", "Robert Jones"}
{
}

//template <typename T>
//std::string Text::name(T id)
//{
//  if (typeid (id) == typeid (e_rank))
//    return "_ranks[static_cast <unsigned int> (id)]";
//}

//template <e_rank>
std::string Text::name(e_rank r)
{
  if (r == e_rank::PRIVATE) // TODO tmp test (need a DB)
    return "PRIVATE";
  return "Fetch error";
}

std::string Text::name(e_terrain t)
{
  if (t == e_terrain::FOREST) // TODO tmp test (need a DB)
    return "FOREST";
  return "Fetch error";
}


std::string Text::getName(int id)
{
  if (id == -1)
    return _names[0];

  return _names[id % _names.size()];
}
