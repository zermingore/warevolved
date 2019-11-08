#include <resources/Resource.hh>
#include <utility>


Resource::Resource(std::string  name)
  : _name (std::move(name))
  , _loaded (false)
  , _fileName ("")
{
}
