#ifndef RESOURCESMANAGER_HH_
# define RESOURCESMANAGER_HH_

# include <rapidxml/rapidxml.hpp>

# include <common/include.hh>
# include <resources/Resource.hh>

# include <resources/Font.hh>
# include <resources/Image.hh>


/** \brief enum matching every resource types
 */
enum e_resource_type
{
  E_RESOURCE_TYPE_NONE = 0, // FIXME rm ?

  E_RESOURCE_TYPE_IMAGE,
  E_RESOURCE_TYPE_FONT,

  E_RESOURCE_TYPE_SOUND, // TODO

  E_RESOURCE_TYPE_NB
};

# define GETIMAGE g_rm->getImage

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
  /** \brief default constructor
   ** initializes resources mapping, calling buildFromXML();
   */
  ResourcesManager();

  /** \brief Constructor, parses the XML, calling buildFromXML()
   ** \param file_name XML file name to parse
   */
  explicit ResourcesManager(const std::string file_name);

  /** \brief Destructor
   */
  ~ResourcesManager();

  // TODO templates
  /** \brief Retrieve an Image from its name (alias)
   ** if the Image wasn't loaded, loads it
   */
  Image *getImage(unsigned int *id, const std::string image_name);

  Image *getImage(const char *image_name);
  Image *getImage(const std::string image_name);

  Font *getFont(const std::string font_name);


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


  std::map<e_resource_type, std::list<Resource*> > _resources; ///< a resources list per type
  std::map<unsigned int, Image*> _images; ///< a resources list per type


private:
  // NOTE think about a list per scope
  e_scope _currentScope; ///< actual context

  std::map<std::string, unsigned int> _mapping; ///< getting resource id by it's name

  rapidxml::xml_document<>* _xml; ///< pointer over XML file
  std::map<e_resource_type, std::string> _typeNames; ///< map categories names with e_resource_type
};

#endif /* !RESOURCESMANAGER_HH_ */
