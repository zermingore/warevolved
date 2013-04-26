#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <resources/Image.hh>


ResourcesManager::ResourcesManager()
{
  this->parseXML("tst.xml");
  buildFromXML();
}

ResourcesManager::ResourcesManager(std::string file_name)
{
  this->parseXML(file_name);
  if (buildFromXML() == -1)
	std::cerr << "FAILURE" << std::endl;
}

ResourcesManager::~ResourcesManager() {
}

void ResourcesManager::initTypeNames()
{
  _typeNames[E_RESOURCE_TYPE_IMAGE] = "images";
  _typeNames[E_RESOURCE_TYPE_FONT] = "fonts";
  _typeNames[E_RESOURCE_TYPE_SOUND] = "sounds";
}


bool ResourcesManager::addResource(e_resource_type type,
								   std::string name,
								   std::string file_name,
								   unsigned int id)
{
  switch (type)
  {
	case E_RESOURCE_TYPE_IMAGE:
	  _resources[type].push_back(new Image(file_name, name, id));
	  return true;
	// case E_RESOURCE_TYPE_FONT:
	//   _resources[current_type].push_back(new Font(file_name, name, id));
	// case E_RESOURCE_TYPE_SOUND:
	//   _resources[current_type].push_back(new Sound(file_name, name, id));
	default:
	  std::cerr << "Unable to match resource type for " <<
		file_name << std::endl;
	  return false;
  }

  return false;
}



Resource* ResourcesManager::getResource(unsigned int id) const
{
  for (unsigned int i = 0; i < E_RESOURCE_TYPE_NB; ++i)
  {
	std::map<int, std::string> m;
	m[0] = "lol";

	std::map<int, std::list<int> > ml;
	ml[0].push_back(2);

	std::list<int> ll;
	ml[0] = ll;
	ll.push_back(42);
	ml[0] = ll;


	std::list<Resource*> lr;
	id = id;

//	std::map<e_resource_type, std::list<Resource*> > _resources; ///< a resources list per type

//	lr = _resources[E_RESOURCE_TYPE_NB];


	//std::list<Resource*> l = _resources[0];

	// for (std::list<Resource*>::iterator it = std::find(ll.begin(), ll.end(), 1))
	//   return it;

	// return _resources[i];

	// std::map<e_resource_type, std::list<Resource*>> _resources; ///< a resources list per type
  }

# ifdef DEBUG
  std::cerr << "unable to find resource of id :" << id << std::endl;
# endif

  return NULL;
}


bool ResourcesManager::parseXML(std::string file_name)
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

#ifdef DEBUG_XML
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

  int current_id = 0;
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
	  std::cout << ">" << str_path << "<" << std::endl;

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

		std::cout << current_type << std::endl;
		std::cout << str_path << "---" << filename << std::endl;
		std::cout << name->value() << std::endl;
		std::cout << current_id << std::endl << std::endl;

		current_id++;
		// this->addResource(current_type,
		// 				  str_path + filename,
		// 				  std::string(name->value()),
		// 				  current_id);

		file = file->next_sibling("file");
	  }

	  folder = folder->next_sibling("folder");
	}

	current_type = static_cast<e_resource_type>(current_type + 1);
	type = type->next_sibling();
  }

  std::cout << _mapping.size() << std::endl;
  std::cout << _mapping["TST"] << std::endl;

  return 0;
}
