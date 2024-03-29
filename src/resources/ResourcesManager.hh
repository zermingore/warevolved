/**
 * \file
 * \date Apr 25, 2013
 * \author Zermingore
 * \namespace resources
 * \brief ResourcesManager (handling Images, Fonts, ...) class declaration
 *   and enum e_resource_type definition
 */

#ifndef RESOURCES_RESOURCES_MANAGER_HH_
# define RESOURCES_RESOURCES_MANAGER_HH_

# include <graphics/graphic_types.hh>
# include <resources/Font.hh>


// # define DEBUG_XML // dump XML mapping resource name <> file

enum class e_resource_type: int; // definition follows


namespace resources {



/**
 * \class ResourcesManager
 * uses a XML file, containing all resources data:
 *   their path, name and specific attributes
 * it manages:
 *   Images
 *   Fonts
 *   Sounds
 */
class ResourcesManager
{
public:
  /**
   * \brief Initialization, parses the XML, calling buildFromXML()
   * \param file_name XML file name to parse
   */
  static void initialize(const std::string& file_name);

  /**
   * \brief If a Texture with the given name exists, return it
   * \return A new Image matching the given name.
   * \note If the Texture doesn't exist, print an error and return a default one
   */
  static std::shared_ptr<graphics::Texture> getTexture(const std::string& name);

  /**
   * \brief If a font with the given name exists, return the matching Font
   * \return A new Font matching the given name.
   *   If the Font does not exist, print an error and return the default one
   */
  static std::shared_ptr<resources::Font> getFont(const std::string& name);



private:
  /**
   * \brief initializes _typeNames array
   */
  static void initTypeNames();

  /**
   * \brief initialize default resources
   * theses resources are used when we cannot find the expected one
   */
  static void initializeDefaultResources();

  /**
   * \brief adds resource to the _resources map
   *   adds it in the right list, according to type
   *
   * \param type Resource media type (image, sound, ...)
   * \param name Resource name (more or less an alias)
   * \param file_name Complete file name (including path and extension)
   *
   * \return true on success
   *   false otherwise
   */
  static bool addResource(const e_resource_type type,
                          const std::string& name,
                          const std::string& file_name);

  /**
   * \brief parses XML file
   * \param file_name file to parse
   *
   * \return true if the file was successfully parsed
   *   false otherwise (prints an error message on std::err)
   */
  static bool parseXML(const std::string& file_name);


# ifdef DEBUG_XML
  /**
   * \brief list all available Resources
   * \note Display resources lists, by categories
   */
  static void listResources();
# endif

  /// Images files list (name [identifier] -> image file name)
  inline static std::map<std::string, std::string> _images;

  /// Textures list (name [identifier] -> pointer on the Texture)
  inline static
  std::map<std::string, std::shared_ptr<graphics::Texture>> _textures;

  /// Fonts list (name [identifier] -> font file name)
  inline static std::map<std::string, std::shared_ptr<Font>> _fonts;

  /// map categories names matching e_resource_type
  inline static std::map<e_resource_type, std::string> _typeNames;
};

} // namespace resources


/**
 * \enum e_resource_type
 * \brief matching every resource types
 */
enum class e_resource_type: int
{
  NONE = 0,

  IMAGE,
  FONT,
  SOUND,
};


#endif /* !RESOURCES_RESOURCES_MANAGER_HH_ */
