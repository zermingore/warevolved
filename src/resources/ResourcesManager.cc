#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <resources/Image.hh>
#include <resources/Font.hh>

# define DEBUG_XML 1
# define DEBUG_XML_FULL 1


ResourcesManager::ResourcesManager(const std::string file_name)
{
  this->parseXML(file_name);
  if (buildFromXML() == -1)
    std::cerr << "build XML FAILURE" << std::endl;

  this->initializeDefaultResources();

# ifdef DEBUG_XML
  this->listResources();
# endif
}


ResourcesManager::~ResourcesManager()
{
  delete _xml;

  for (unsigned int i = E_RESOURCE_TYPE_NONE; i < E_RESOURCE_TYPE_NB; ++i)
  {
    e_resource_type type = static_cast<e_resource_type>(i);
    for (auto it: _resources[type])
      delete it;
  }
}


void ResourcesManager::initializeDefaultResources()
{
  _resources[E_RESOURCE_TYPE_IMAGE].push_back(
    new Font("resources/defaults/image.png", "default", 0));
  _resources[E_RESOURCE_TYPE_FONT].push_back(
    new Font("resources/defaults/font.ttf", "default", 0));
}

void ResourcesManager::initTypeNames()
{
  _typeNames[E_RESOURCE_TYPE_NONE] = "none";
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
	  std::cout << "Image detected: " << file_name << std::endl;
      _images[id] = new Image(file_name, name, id);
      _resources[type].push_back(_images[id]);
      return true;

    case E_RESOURCE_TYPE_FONT:
	  std::cout << "Font detected" << std::endl;
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

  for (auto it : _resources[E_RESOURCE_TYPE_IMAGE])
  {
    if (it->getName() == image_name)
    {
      if (!it->getLoaded())
        it->load();

      *id = (it->getId());

      return dynamic_cast <Image*> (it);
    }
  }

  Debug::logPrintf("Unable to find image ", image_name, " using default");

  return _images[0];
}


Image *ResourcesManager::getImage(const char *image_name)
{
  std::string str = std::string(image_name);

  unsigned int id = 0;
  if ((id = _mapping[str]))
    return _images[id];

  for (auto it : _resources[E_RESOURCE_TYPE_IMAGE])
  {
    if (it->getName() == str)
    {
      if (!it->getLoaded())
        it->load();

      _mapping[str] = (it->getId());

      return dynamic_cast <Image*> (it);
    }
  }

# ifdef DEBUG
  std::cerr << "Unable to find image " << image_name << std::endl;
# endif

  // return a default image
  return _images[0];
}


Image *ResourcesManager::getImage(const std::string image_name)
{
  unsigned int id = 0;
  if ((id = _mapping[image_name]))
    return _images[id];

  for (auto it : _resources[E_RESOURCE_TYPE_IMAGE])
  {
    if (it->getName() == image_name)
    {
      if (!it->getLoaded())
        it->load();

      _mapping[image_name] = (it->getId());

      return dynamic_cast <Image*> (it);
    }
  }

# ifdef DEBUG
  std::cerr << "Unable to find image " << image_name << std::endl;
# endif

  // return a default image
  return _images[0];
}


Font *ResourcesManager::getFont(const std::string font_name)
{
  return new Font("resources/fonts/army.ttf", font_name, 0); // leak

  std::cout << "Size: " << _resources[E_RESOURCE_TYPE_FONT].size() << std::endl;

  for (auto it : _resources[E_RESOURCE_TYPE_FONT])
  {
    std::cout << font_name << " expected, found " << it << std::endl;
    if (it->getName() == font_name)
    {
      if (!it->getLoaded())
        it->load();

      return dynamic_cast <Font*> (it);
    }
  }

# ifdef DEBUG
  // TODO reaching this without Valgrind
  Debug::logPrintf("Unable to find font", font_name);
# endif

  // return a default font
  return new Font("resources/fonts/army.ttf", font_name, 0); // leak
}


bool ResourcesManager::parseXML(const std::string file_name)
{
  // Open stream
  std::basic_ifstream <char> stream(file_name);
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
  stream.read(&xml_data.front(), static_cast <unsigned int> (size));
  xml_data[size] = 0;

# ifdef DEBUG_XML_FULL
  // prints whole XML
  for (auto i: xml_data)
    std::cout << i;
# endif

  _xml = new (rapidxml::xml_document<>);
  if (!_xml)
  {
	std::cerr << "Unable to create a new XML document";
	return false;
  }

  _xml->parse<0> (&xml_data[0]);

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

  unsigned int id = 0; // 0: reserved (unset values, ...)
  type = resources->first_node(_typeNames[current_type].c_str());
  while (current_type < E_RESOURCE_TYPE_NB) // for all categories
  {
	std::cerr << "current tn: " << _typeNames[current_type].c_str() << std::endl;

#   ifdef DEBUG
    if (!type)
    {
      std::cerr << "type is NULL" << std::endl <<
          "tried to match> " << _typeNames[current_type] << std::endl;
      return -1;
    }
#   endif

    // std::cout << "type: " << type << std::endl;
    // std::cout << "type 1st node 'folder': " << type->first_node("folder") << std::endl;
    // std::cout << "type 1st node: " << type->first_node() << std::endl;
    // std::cout << "type 1st node name: " << type->first_node()->name() << std::endl;
    folder = type->first_node("folder");

#   ifdef DEBUG
    if (!folder)
	  std::cerr << "folder is NULL" << std::endl << std::endl;
#   endif

    while (folder)
    {
      path = folder->first_attribute();
      file = folder->first_node("file");
      //const std::string str_path = path->value();

      const char *str_path = path->value();


#     ifdef DEBUG
      // testing if last char is effectively a FOLDER_SEPARATOR
      //if (*(str_path.end() - 1) != FOLDER_DELIMITER)
      //      if (str_path[strlen(str_path) - 2] != FOLDER_DELIMITER)
      //      {
      //        std::cerr << ">>ERROR<< XML file:" << std::endl <<
      //          "-- Missing trailing folder delimiter in " << str_path << std::endl;
      //      }

      if (!path)
      {
        std::cerr << "XML file: Missing path" << std::endl;
        return -1;
      }

      if (!file)
        std::cerr << ">Warning< XML file: empty folder " << str_path << std::endl;
#     endif

      while (file)
      {
        const char *filename = file->first_attribute()->value();
        name = file->first_node("name");
        std::string tmp = str_path;
        tmp += filename;
        this->addResource(current_type, name->value(), tmp, id++);
        file = file->next_sibling("file");
      }

      folder = folder->next_sibling("folder");
    }

    DEBUG_PRINT("nb_type++");
    current_type = static_cast<e_resource_type>(current_type + 1);
    type = type->next_sibling();
  }

  return 0;
}


#ifdef DEBUG_XML
void ResourcesManager::listResources()
{
  std::cout << "\t\t__________Resources List__________" << std::endl;

  for (auto i = E_RESOURCE_TYPE_NONE + 1; i < E_RESOURCE_TYPE_NB; ++i)
  {
    e_resource_type type = static_cast<e_resource_type>(i);
    std::cout << "Category: " << _typeNames[type] << std::endl;
    for (auto it : _resources[type])
    {
      std::cout << it->getFileName() << '\t'
                << it->getName() << '\t'
                << it->getId() << std::endl;
    }
  }
}
#endif
