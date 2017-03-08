#include <resources/Resource.hh>

Resource::Resource(std::string name)
  : _name (name)
  , _loaded (false)
  , _fileName ("")
{
}
