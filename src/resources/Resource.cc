#include <resources/Resource.hh>


Resource::Resource(const std::string name)
  : _name (name)
  , _loaded (false)
  , _fileName ("")
{
}
