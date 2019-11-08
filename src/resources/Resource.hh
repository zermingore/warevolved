/**
 * \file
 * \date April 25, 2013
 * \brief Resource abstract class declaration
 */

#ifndef RESOURCES_RESOURCE_HH_
# define RESOURCES_RESOURCE_HH_

# include <string>


/**
 * \class Resource
 * \brief generic Resource class
 * \note Daughters classes: Image, Font, ...
 */
class Resource
{
public:
  /**
   * \brief Default Constructor
   */
  Resource() = default;

  /**
   * \brief Constructor
   * \param name resource name
   */
  explicit Resource(std::string  name);

  /**
   * \brief default destructor
   */
  virtual ~Resource() = default;


  /**
   * \brief resource loading
   * \todo remove (must be in the Ctor)
   */
  virtual bool load() {
    return false;
  }

  /**
   * \brief unloads a resource
   * \todo virtual pure
   */
  virtual void unload() { }

  /**
   * \brief _loaded boolean getter
   * \return A boolean to know if the resource is already in RAM
   */
  auto getLoaded() const {
    return _loaded;
  }

  /**
   * \brief _fileName getter
   * \return _fileName : Resource full file name (with path and extension)
   */
  auto getFileName() const {
    return _fileName;
  }

  /**
   * \brief _fileName setter
   * \param file_name New resource file name
   */
  void setFileName(const std::string& file_name) {
    _fileName = file_name;
  }

  /**
   * \brief _name getter
   * \return _name: Resource alias
   * \note _name could be an empty string
   */
  auto name() const {
    return _name;
  }

  /**
   * \brief _name setter
   * \param name New resource alias name
   */
  void setName(const std::string& name) {
    _name = name;
  }


protected:
  std::string _name;     ///< Resource alias name
  bool _loaded;          ///< Is the resource already in RAM ?
  std::string _fileName; ///< Resource file name (with full path and extension)
};

#endif /* !RESOURCES_RESOURCE_HH_ */
