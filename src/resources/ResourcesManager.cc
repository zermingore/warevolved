#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <resources/Image.hh>
#include <resources/Font.hh>


ResourcesManager::ResourcesManager() {
}

ResourcesManager::ResourcesManager(const std::string file_name)
{
  this->parseXML(file_name);
  if (buildFromXML() == -1)
	std::cerr << "FAILURE" << std::endl;

#ifdef DEBUG_XML
  this->listResources();
#endif
}

ResourcesManager::~ResourcesManager()
{
  delete _xml;

  for (unsigned int i = E_RESOURCE_TYPE_NONE + 1; i < E_RESOURCE_TYPE_NB; ++i)
  {
	e_resource_type type = static_cast<e_resource_type>(i);
	for (auto it = _resources[type].begin(); it != _resources[type].end(); ++it)
	  delete *it;
  }
}

void ResourcesManager::initTypeNames()
{
  _typeNames[E_RESOURCE_TYPE_IMAGE] = "images";
  _typeNames[E_RESOURCE_TYPE_FONT] = "fonts";
  _typeNames[E_RESOURCE_TYPE_SOUND] = "sounds";
}


bool ResourcesManager::addResource(e_resource_type type,
								   const std::string name,
								   const std::string file_name,
								   unsigned int id)
{
  switch (type)
  {
	case E_RESOURCE_TYPE_IMAGE:
	  _images[id] = new Image(file_name, name, id);
	  _resources[type].push_back(_images[id]);
	  return true;
	case E_RESOURCE_TYPE_FONT:
	  _resources[type].push_back(new Font(file_name, name, id));
	  return true;
	// case E_RESOURCE_TYPE_SOUND:
	//   _resources[type].push_back(new Sound(file_name, name, id));
	// return true;

	default:
	  std::cerr << file_name << ": Unknown resource type" << std::endl;
	  return false;
  }

  return false;
}


Image *ResourcesManager::getImage(unsigned int *id, const std::string image_name)
{
  if (*id)
	return _images[*id];

  for (auto it = _resources[E_RESOURCE_TYPE_IMAGE].begin(); it != _resources[E_RESOURCE_TYPE_IMAGE].end(); ++it)
  {
	if ((*it)->getName() == image_name)
	{
	  if (!(*it)->getLoaded())
		(*it)->load();

	  *id = ((*it)->getId());

	  return dynamic_cast <Image*> (*it);
	}
  }

# ifdef DEBUG
  std::cerr << "Unable to find image " << image_name << std::endl;
# endif

  return NULL; // NOTE return a default image
}



Font *ResourcesManager::getFont(const std::string font_name)
{
  for (auto it = _resources[E_RESOURCE_TYPE_FONT].begin(); it != _resources[E_RESOURCE_TYPE_FONT].end(); ++it)
  {
	if ((*it)->getName() == font_name)
	{
	  if (!(*it)->getLoaded())
		(*it)->load();

	  return dynamic_cast <Font*> (*it);
	}
  }

# ifdef DEBUG
  std::cerr << "Unable to find font " << font_name << std::endl;
# endif

  return NULL; // NOTE return a default font ?
}


// unsigned int ResourcesManager::getResourceId(std::string resource_name)
// {
//   // TODO split Image, Sound, ...

//   std::cout << "shd NOT call" << std::endl;

//   // if ()

//   return _mapping[resource_name];
// }


bool ResourcesManager::parseXML(const std::string file_name)
{
  // Open stream
  std::basic_ifstream<char> stream(file_name);
  if (!stream)
  {
	std::cerr << "XML: input error" << std::endl;
  	return false;
  }
  stream.unsetf(std::ios::skipws); // skip white spaces

  // get stream size
  stream.seekg(0, std::ios::end);
  size_t size = stream.tellg();
  stream.seekg(0);

  // Load data and add terminating 0
  std::vector<char> xml_data;
  xml_data.resize(size + 1);
  stream.read(&xml_data.front(), static_cast<unsigned int>(size));
  xml_data[size] = 0;

#ifdef DEBUG_XML_FULL
  // prints whole XML
  for(std::vector<char>::const_iterator i = xml_data.begin(); i != xml_data.end(); ++i)
	std::cout << *i;
#endif

  _xml = new (rapidxml::xml_document<>);
  _xml->parse<0>(&xml_data[0]);

  return true;
}


int ResourcesManager::buildFromXML()
{
  this->initTypeNames(); // building _typeNames

  e_resource_type current_type = static_cast<e_resource_type>(E_RESOURCE_TYPE_NONE + 1);
  rapidxml::xml_node<> *resources = _xml->first_node("resources");
  rapidxml::xml_node<> *type; // XML tag: images, fonts, sounds, ...
  rapidxml::xml_node<> *folder, *file, *name;
  rapidxml::xml_attribute<> *path;

  unsigned int id = 1; // 0: reserved (unset values, ...)
  type = resources->first_node(_typeNames[current_type].c_str());
  while (current_type < E_RESOURCE_TYPE_NB) // for all categories
  {
#   ifdef DEBUG
	if (!type)
	{
	  std::cerr << "type is NULL" << std::endl <<
		"tried to match>" << _typeNames[current_type].c_str() << std::endl;
	  return -1;
	}
#   endif

	folder = type->first_node("folder");
	while (folder)
	{
	  path = folder->first_attribute();
	  file = folder->first_node("file");
	  const std::string str_path = std::string(path->value());

#    ifdef DEBUG
	  // testing if last char is effectively a FOLDER_SEPARATOR
	  if (*(str_path.end() - 1) != FOLDER_DELIMITER)
	  {
		std::cerr << ">>ERROR<< XML file:" << std::endl <<
		  "-- Missing trailing folder delimiter in " << str_path << std::endl;
	  }

	  if (!path)
	  {
		std::cerr << "XML file: Missing path" << std::endl;
		return -1;
	  }

	  if (!file)
		std::cerr << ">Warning< XML file: empty folder " << str_path << std::endl;
#   endif

	  while (file)
	  {
		std::string filename = std::string(file->first_attribute()->value());
		name = file->first_node("name");
		this->addResource(current_type, name->value(), str_path + filename, id++);
		file = file->next_sibling("file");
	  }

	  folder = folder->next_sibling("folder");
	}

	current_type = static_cast<e_resource_type>(current_type + 1);
	type = type->next_sibling();
  }

  return 0;
}


#ifdef DEBUG
void ResourcesManager::listResources()
{
  std::cout << "\t\tResources List" << std::endl;

  for (unsigned int i = E_RESOURCE_TYPE_NONE + 1; i < E_RESOURCE_TYPE_NB; ++i)
  {
	e_resource_type type = static_cast<e_resource_type>(i);
	std::cout << "Category: " << _typeNames[type] << std::endl;
	for (auto it = _resources[type].begin(); it != _resources[type].end(); ++it)
	{
	  std::cout << (*it)->getFileName() << '\t'
				<< (*it)->getName() << '\t'
				<< (*it)->getId() << std::endl;
	}
  }
}
#endif
