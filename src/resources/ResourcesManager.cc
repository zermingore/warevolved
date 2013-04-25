#include <resources/ResourcesManager.hh>
#include <common/constants.hh>


ResourcesManager::ResourcesManager()
{
  this->parseXML("tst.xml");
  buildFromXML();
}

ResourcesManager::ResourcesManager(std::string file_name)
{
  this->parseXML(file_name);
  buildFromXML();
}

ResourcesManager::~ResourcesManager() {
}

void ResourcesManager::initTypeNames()
{
  _typeNames[E_RESOURCE_TYPE_IMAGE] = "images";
  _typeNames[E_RESOURCE_TYPE_FONT] = "fonts";
  _typeNames[E_RESOURCE_TYPE_SOUND] = "sounds";
}


Resource* ResourcesManager::getResource(unsigned int id) const
{
  //return _resources[id];
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
  rapidxml::xml_node<>* resources = _xml->first_node("resources");
  rapidxml::xml_node<>* type = resources->first_node(_typeNames[current_type].c_str());
  rapidxml::xml_node<>* folder = type->first_node("folder");

#ifdef DEBUG
  if (!folder)
  	std::cerr << "empty folder" << std::endl;
#endif

  rapidxml::xml_node<>* file;
  rapidxml::xml_node<>* name;
  rapidxml::xml_attribute<>* filename;
  rapidxml::xml_attribute<>* path;


  while (current_type < E_RESOURCE_TYPE_NB) // for all categories
  {
	int current_id = 0;
	type = resources->first_node(_typeNames[current_type].c_str());
	folder = type->first_node("folder");

	while (folder)
	{
	  path = folder->first_attribute();
	  file = folder->first_node("file");

#   ifdef DEBUG // UNIX Specific bunch of code (folder separator)
	  // testing last char is effectively a '/'
	  std::string str = path->value();
	  if (*(str.end() - 1) != FOLDER_DELIMITER)
	  {
		std::cerr << "XML file: possible folder error:" << std::endl
				  << "missing trailing folder delimiter in " << str << std::endl;
	  }
#   endif

	  while (file)
	  {
		filename = file->first_attribute();

		std::string tst = std::string(path->value()) + std::string(filename->value());
		std::cout << ">> " << tst << std::endl;

		name = file->first_node("name");
		std::cout << name->value() << std::endl;

		_mapping[name->value()] = current_id++;

		file = file->next_sibling("file");
	  }

	  folder = folder->next_sibling("folder");
	}

	current_type = static_cast<e_resource_type>(current_type + 1);
  }

  folder = type->first_node("folder");

  std::cout << _mapping.size() << std::endl;
  std::cout << _mapping["TST"] << std::endl;

  return 0;
}
