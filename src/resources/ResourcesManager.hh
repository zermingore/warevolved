#ifndef RESOURCESMANAGER_HH_
# define RESOURCESMANAGER_HH_

# include <common/include.hh>
# include <common/macros.hh>
# include <rapidxml/rapidxml.hpp>
# include <resources/Resource.hh>
# include <resources/Font.hh>
# include <resources/Image.hh>


# define DEBUG_XML 1

/** \brief enum matching every resource types
 */
enum e_resource_type
{
  E_RESOURCE_TYPE_NONE = 0,

  E_RESOURCE_TYPE_IMAGE,
  E_RESOURCE_TYPE_FONT,
  E_RESOURCE_TYPE_SOUND, // TODO sound management

  E_RESOURCE_TYPE_NB
};


/** \brief ResourcesManager class
 ** uses a XML file, containing all resources data:
 **   their path, name and specific attributes
 ** it manages:
 **   Images
 **   Fonts
 **   Sounds
 */
class ResourcesManager
{
public:
  /** \brief Constructor, parses the XML, calling buildFromXML()
   ** \param file_name XML file name to parse
   */
  explicit ResourcesManager(const std::string file_name);

  /** \brief initialize default resources
   ** theses resources are used when we cannot find the expected one
   */
  void initializeDefaultResources();

  // TODO templates
  /** \brief Retrieve an Image from its name (alias)
   ** if the Image wasn't loaded, loads it
   */
  Image& getImage(unsigned int *id, const std::string image_name);
  Image& getImage(const char *image_name);
  Image& getImage(const std::string image_name);

  /** \brief Retrieve a Font from its name (alias)
   ** if the Font wasn't loaded, loads it
   */
  Font& getFont(const std::string font_name);


private:
  /** \brief initializes _typeNames array
   */
  void initTypeNames();

  /** \brief adds resource to the _resources map
   **   adds it in the right list, according to type
   **
   ** \param type Resource media type (image, sound, ...)
   ** \param name Resource name (more or less an alias)
   ** \param file_name Complete file name (including path and extension)
   ** \param id Unique resource id
   **
   ** \return true on success
   **   false otherwise
   */
  bool addResource(e_resource_type type,
                   const std::string name,
                   const std::string file_name,
                   unsigned int id);

  /** \brief parses XML file
   ** \param file_name file to parse
   **
   ** \return true if the file was successfully parsed
   **   false otherwise (prints an error message on std::err)
   */
  bool parseXML(const std::string file_name);

  /** \brief builds the global std::map containing all resources
   ** \return 0 on success
   **   -1 on failure
   **   a strictly positive value corresponding to the number of unmatched files
   ** should be called only one time (when launching the game)
   ** very long execution time [function of number of resources]
   ** adds every XML entry to the std::map _resources
   */
  int buildFromXML();


# ifdef DEBUG_XML
  /** \brief list all available Resources
   ** it displays resources lists, by categories
   */
  void listResources();
# endif


  ///< a resources list per type
  std::map<e_resource_type, std::list<std::shared_ptr<Resource>>> _resources;
  std::map<unsigned int, std::shared_ptr<Image>> _images; ///< an Image list

  // NOTE: as we're using a few font, we use a std::string
  //   furthermore, here, we don't care about the overhead
  std::map<std::string, std::shared_ptr<Font>> _fonts; ///< a Font list

  // NOTE think about a list per scope (or a map of map, with 2nd index: scope)
  e_scope _currentScope; ///< actual context

  ///< getting resource id by it's name
  std::map<std::string, unsigned int> _mapping;

  ///< unique pointer on resources XML file
  std::unique_ptr<rapidxml::xml_document<>> _xml;

  ///< map categories names with e_resource_type
  std::map<e_resource_type, std::string> _typeNames;
};

#endif /* !RESOURCESMANAGER_HH_ */
