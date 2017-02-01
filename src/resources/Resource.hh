#ifndef RESOURCE_HH_
# define RESOURCE_HH_

# include <common/include.hh>

// should split scopes ?
// (menu_scopes) with main, end game, network


/**
 * \brief various scopes to delimit resources lifetime
 * *Warning*: unused for now
 */
enum e_scope
{
  E_SCOPE_MAIN_MENU,

  E_SCOPE_ANY_GAME, ///< in-game_menu, cursor
  E_SCOPE_SNOWY,
  E_SCOPE_SUNNY,

  E_SCOPE_ALL ///< the resource will be present in any scope
};


/**
 * \brief generic Resource class
 * Resource is an abstract class
 * Its daughters are Image, Sound, ...
 */
class Resource
{
public:
  /**
   * \brief Default Constructor
   */
  Resource() {}
  /**
   * \brief Constructor
   * \param name resource name
   */
  explicit Resource(std::string name);
  virtual ~Resource() {}

  /**
   * \brief virtual method: resource loading
   */
  virtual bool load() = 0;
  virtual void unload() {}

  bool getLoaded() { return _loaded; }

  /**
   * \brief _fileName getter
   * \return _fileName : Resource full file name (with path and extension)
   */
  std::string getFileName() const { return _fileName; }

  /**
   * \brief _fileName setter
   *   sets _fileName to file_name
   * \param file_name Resource File Name to put into _fileName
   */
  void setFileName(std::string file_name) { _fileName = file_name; }

  /**
   * \brief _name getter
   * \return _name : Resource alias
   *   _name could be an empty string
   */
  std::string name() const { return _name; }

  /**
   * \brief _name setter
   *   sets _name to name
   * \param name Resource alias name to put into _name
   */
  void setName(std::string name) { _name = name; }


protected:
  std::string _name; ///< Resource alias name
  bool _loaded; ///< is the resource already in RAM ?
  //e_scope _scope; ///< resource scope (the context it belongs to)
  std::string _fileName; ///< Resource file name (with full path and extension)
};

#endif /* !RESOURCE_HH_ */
