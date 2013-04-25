#include <resources/Resource.hh>


Resource::Resource() :
  _id (0),
  _fileName (""),
  _loaded (false),
  _scope (E_SCOPE_ALL)
{
}

Resource::~Resource() // shd be virtual pure
{
}


std::string Resource::getFileName() const {
  return _fileName;
}

void Resource::setFileName(std::string file_name) {
  _fileName = file_name;
}
