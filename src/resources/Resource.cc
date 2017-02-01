#include <resources/Resource.hh>

Resource::Resource(std::string name)
  : _name (name)
  , _fileName ("")
  , _loaded (false)
  //_scope (E_SCOPE_ALL)
{
}
