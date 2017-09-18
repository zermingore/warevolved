#include <resources/ResourcesManager.hh>

#include <lib/pugixml.hh>
#include <resources/Sprite.hh>
#include <resources/Font.hh>
#include <debug/Debug.hh>



namespace resources {

// Static Variables definition
std::map<std::string, std::string> ResourcesManager::_images;
std::map<std::string, std::shared_ptr<resources::Font>> ResourcesManager::_fonts;
std::map<e_resource_type, std::string> ResourcesManager::_typeNames;

// default resources paths
const std::string DEFAULT_IMAGE_PATH = "resources/defaults/image.png";
const std::string DEFAULT_FONT_PATH  = "resources/defaults/font.ttf";



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
  _images["default"] = DEFAULT_IMAGE_PATH;
  _fonts["default"]  = std::make_shared<resources::Font> (DEFAULT_FONT_PATH, "defaut");
}

void ResourcesManager::initTypeNames()
{
  _typeNames[e_resource_type::NONE]  = "none";
  _typeNames[e_resource_type::IMAGE] = "images";
  _typeNames[e_resource_type::FONT]  = "fonts";
  _typeNames[e_resource_type::SOUND] = "sounds";
}


bool ResourcesManager::addResource(const e_resource_type type,
                                   const std::string name,
                                   const std::string file_name)
{
  switch (type)
  {
    case e_resource_type::IMAGE:
      _images[name] = file_name;
      return true;

    case e_resource_type::FONT:
      _fonts[name] = std::make_shared<resources::Font> (file_name, name);
      return true;

    // case e_resource_type::SOUND:
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
    ERROR("unable to load file");
    return false;
  }

  auto type = static_cast<e_resource_type>(static_cast<int> (e_resource_type::NONE) + 1);
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

        for (pugi::xml_node child: file.children()) {
          addResource(type, child.text().get(), tmp);
        }
      }
    }

    type = static_cast<e_resource_type>(static_cast<int> (type) + 1);
    category = category.next_sibling();
  }

  return true;
}


#ifdef DEBUG_XML
void ResourcesManager::listResources()
{
  PRINTF("\t\t__________Resources List__________");
  for (auto it : _images) {
    Debug::logPrintf(it.second->name());
  }

  for (auto it : _fonts) {
    Debug::logPrintf(it.second->name());
  }
}
#endif // DEBUG_XML


std::shared_ptr<resources::Sprite> ResourcesManager::getSprite(const std::string name)
{
  if (_images.find(name) != _images.end()) {
    return std::make_shared<resources::Sprite> (_images[name], name);
  }

  ERROR("Unable to find image:", name);

  return std::make_shared<resources::Sprite> (DEFAULT_IMAGE_PATH, "default");
}



std::shared_ptr<resources::Font> ResourcesManager::getFont(const std::string name)
{
  if (_fonts.find(name) != _fonts.end()) {
    return _fonts[name];
  }

  // ERROR("Unable to find font: ", name);

  return _fonts["default"];
}



} // namespace resources
