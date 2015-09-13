#include <resources/ResourcesManager.hh>
#include <pugixml/pugixml.hpp>
#include <common/constants.hh>
#include <resources/Image.hh>
#include <resources/Font.hh>


namespace resources
{
// Static Variables definition
std::map<std::string, std::shared_ptr<graphics::Image>> ResourcesManager::_images;
std::map<std::string, std::shared_ptr<Font>> ResourcesManager::_fonts;
std::map<e_resource_type, std::string> ResourcesManager::_typeNames;


// default resources paths
const std::string DEFAULT_IMAGE_PATH = "resources/defaults/image.png";
const std::string DEFAULT_FONT_PATH = "resources/defaults/font.ttf";


void ResourcesManager::initialize(const std::string file_name)
{
  initTypeNames();
  initializeDefaultResources();
  parseXML(file_name);

# ifdef DEBUG_XML
  listResources();
# endif
}


void ResourcesManager::initializeDefaultResources()
{
  _images["default"] = std::make_shared<graphics::Image> (DEFAULT_IMAGE_PATH, "default");
  _fonts["default"] = std::make_shared<Font> (DEFAULT_FONT_PATH, "default");
}

void ResourcesManager::initTypeNames()
{
  _typeNames[E_RESOURCE_TYPE_NONE]  = "none";
  _typeNames[E_RESOURCE_TYPE_IMAGE] = "images";
  _typeNames[E_RESOURCE_TYPE_FONT]  = "fonts";
  _typeNames[E_RESOURCE_TYPE_SOUND] = "sounds";
}


bool ResourcesManager::addResource(e_resource_type type,
                                   const std::string name,
                                   const std::string file_name)
{
  switch (type)
  {
    case E_RESOURCE_TYPE_IMAGE:
      _images[name] = std::make_shared<graphics::Image> (file_name, name);
      return true;

    case E_RESOURCE_TYPE_FONT:
    {
      _fonts[name] = std::make_shared<Font> (file_name, name);
      return true;
    }

    // case E_RESOURCE_TYPE_SOUND:
    //   _sounds[name] = std::make_shared<Sound> (file_name, name);
    //   return true;

    default:
      Debug::logPrintf(file_name, ": Unknown resource type");
      return false;
  }
}


bool ResourcesManager::parseXML(const std::string file_name)
{
  pugi::xml_document doc;
  if (!doc.load_file(file_name.c_str()))
  {
    Debug::error("unable to load file");
    return false;
  }

  e_resource_type type = static_cast<e_resource_type>(E_RESOURCE_TYPE_NONE + 1);
  pugi::xml_node category = doc.child("resources").child(_typeNames[type].c_str());

  // for all categories > browse folders > for all files > get their infos
  while (category)
  {
    for (pugi::xml_node folder: category.children("folder"))
    {
      for (pugi::xml_node file: folder.children())
      {
        std::string tmp = folder.attribute("path").value();
        tmp += file.attribute("filename").value();

        for (pugi::xml_node child: file.children())
          addResource(type, child.text().get(), tmp);
      }
    }

    type = static_cast<e_resource_type>(type + 1);
    category = category.next_sibling();
  }

  return true;
}


#ifdef DEBUG_XML
void ResourcesManager::listResources()
{
  PRINTF("\t\t__________Resources List__________");
  for (auto it : _images)
    Debug::logPrintf(it.second->name());

  for (auto it : _fonts)
    Debug::logPrintf(it.second->name());
}
#endif


graphics::Image& ResourcesManager::getImage(const std::string name)
{
  if (_images.find(name) != _images.end())
    return *_images[name];

  Debug::error("Unable to find image", name);

  return *_images["default"];
}


Font& ResourcesManager::getFont(const std::string name)
{
  if (_fonts.find(name) != _fonts.end())
    return *_fonts[name];

  Debug::logPrintf("Unable to find font", name);

  return *_fonts["default"];
}


} // namespace resources
