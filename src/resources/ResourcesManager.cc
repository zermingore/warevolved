#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <resources/Image.hh>
#include <resources/Font.hh>
#include <cstring> // strlen

#define DEBUG_XML
#define DEBUG_XML_FULL


ResourcesManager::ResourcesManager(const std::string file_name)
{
  parseXML(file_name);
  if (buildFromXML() == -1)
    std::cerr << "build XML FAILURE" << std::endl;

  initializeDefaultResources();

# ifdef DEBUG_XML
  listResources();
# endif
}


void ResourcesManager::initializeDefaultResources()
{
  _images["default"].reset(new Image(DEFAULT_IMAGE_PATH, "default"));
  _fonts["default"].reset(new Font(DEFAULT_FONT_PATH, "default"));
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
                                   const std::string file_name)
{
  //PRINTF("--------- add", name, file_name);
  switch (type)
  {
    case E_RESOURCE_TYPE_IMAGE:
      _images[name].reset(new Image(file_name, name));
      return true;

    case E_RESOURCE_TYPE_FONT:
    {
      _fonts[name].reset(new Font(file_name, name));
      return true;
    }

    // case E_RESOURCE_TYPE_SOUND:
    //   _resources[type].push_back(new Sound(file_name, name, id));
    //   return true;

    default:
      Debug::logPrintf(file_name, ": Unknown resource type");
      return false;
  }

  return false;
}


Image& ResourcesManager::getImage(const std::string name)
{
  if (_images.find(name) != _images.end())
    return *_images[name];

  for (auto it: _images)
  {
    if (it.first == name)
    {
      if (!it.second->getLoaded())
        it.second->load();

      return dynamic_cast <Image&> (*it.second);
    }
  }

  Debug::logPrintf("Unable to find image", name);

  // return a default image
  return *_images["default"];
}


Font& ResourcesManager::getFont(const std::string name)
{
  if (_fonts.find(name) != _fonts.end())
    return *_fonts[name];

  Debug::logPrintf("Unable to find font", name);

  // return a default font
  return *_fonts["default"];
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
  std::cout << std::endl;
# endif

  _xml.reset(new rapidxml::xml_document<>);
  if (!_xml)
  {
    Debug::logPrintf("Unable to create a new XML document");
	return false;
  }

  _xml->parse<(0)> (&xml_data[0]);

  return true;
}


int ResourcesManager::buildFromXML()
{
  initTypeNames(); // building _typeNames

  e_resource_type current_type = static_cast<e_resource_type>(E_RESOURCE_TYPE_NONE + 1);
  rapidxml::xml_node<> *resources = _xml->first_node("resources");
  rapidxml::xml_node<> *type; // XML tag: images, fonts, sounds, ...
  rapidxml::xml_node<> *folder, *file, *name;
  rapidxml::xml_attribute<> *path;

  type = resources->first_node(_typeNames[current_type].c_str());

  while (current_type < E_RESOURCE_TYPE_NB) // for all categories
  {
#   ifdef DEBUG
    if (!type)
    {
      Debug::logPrintf("Type is NULL\n Tried to match>", _typeNames[current_type]);
      return -1;
    }
#   endif

    folder = type->first_node("folder");

#   ifdef DEBUG
    std::cout << type->name() << std::endl;

    if (!folder)
      PRINTF("folder is NULL");
#   endif

    while (folder)
    {
      path = folder->first_attribute();
      file = folder->first_node("file");
      const char *str_path = path->value();

#     ifdef DEBUG
      // testing if last char is effectively a FOLDER_SEPARATOR
      // if ((str_path[std::strlen(str_path) - 1]) != FOLDER_DELIMITER)
      // {
      //   Debug::logPrintf(
      //     ">>ERROR<< XML file: Missing trailing folder delimiter: ", str_path);
      // }

      if (!path)
      {
        Debug::logPrintf("XML file: Missing path");
        return -1;
      }

      if (!file)
        Debug::logPrintf(">Warning< XML file: empty folder ", str_path);
#     endif

      while (file)
      {
        const char *filename = file->first_attribute()->value();
        name = file->first_node("name");
        std::string tmp = str_path;
        tmp += filename;
        addResource(current_type, name->value(), tmp);
        file = file->next_sibling("file");
      }

      folder = folder->next_sibling("folder");
    }

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
    for (auto it : _images)
      Debug::logPrintf(it.second->name());

    for (auto it : _fonts)
      Debug::logPrintf(it.second->name());
  }
}
#endif
