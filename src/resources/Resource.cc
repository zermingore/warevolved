#include <resources/Resource.hh>


Resource::Resource() :
  _id (0),
  _fileName (""),
  _loaded (false),
  _scope (E_SCOPE_ALL)
{
}

Resource::Resource(std::string name) :
  _id (0),
  _fileName (""),
  _name (name),
  _loaded (false),
  _scope (E_SCOPE_ALL)
{
}

Resource::Resource(std::string name, unsigned int id) :
  _id (id),
  _name (name),
  _loaded (false),
  _scope (E_SCOPE_ALL)
{
}

Resource::~Resource() {
}

bool Resource::getLoaded() {
  return _loaded;
}

std::string Resource::getFileName() const {
  return _fileName;
}

void Resource::setFileName(std::string file_name) {
  _fileName = file_name;
}

std::string Resource::name() const {
  return _name;
}

void Resource::setName(std::string name) {
  _name = name;
}

unsigned int Resource::getId() const {
  return _id;
}

void Resource::setid(unsigned int id) {
  _id = id;
}
