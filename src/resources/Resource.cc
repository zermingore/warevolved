#include <resources/Resource.hh>

Resource::Resource(std::string name) :
  _fileName (""),
  _name (name),
  _loaded (false)
  //_scope (E_SCOPE_ALL)
{
}
