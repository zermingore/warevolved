#include <interface/menus/MenuMap.hh>


namespace interface {


void MenuMap::build()
{
  addCancelEntry( [=] { cancel(); } );
}


} // namespace interface
