#ifndef RESOURCE_HH_
# define RESOURCE_HH_

# include <common/include.hh>

// should split scopes ?
// (menu_scopes) with main, end game, network

/** \brief various scopes to delimit resources lifetime
 */
enum e_scope
{
  E_SCOPE_MAIN_MENU,

  E_SCOPE_ANY_GAME, ///< in-game_menu, cursor
  E_SCOPE_SNOWY,
  E_SCOPE_SUNNY,

  E_SCOPE_ALL ///< the resource will be present in any scope
};


/** \brief generic Resource class
 ** Resource is an abstract class
 ** Its daughters are Image, Sound, ...
 */
class Resource
{
public:
  /** \brief Default Constructor
   */
  Resource();
  explicit Resource(std::string name);
  Resource(std::string name, unsigned int id);
  virtual ~Resource();

  /** \brief virtual method: resource loading
   */
  virtual bool load() = 0;
  virtual void unload() = 0;

  bool getLoaded();

  /** \brief _fileName getter
   ** \return _fileName : Resource full file name (with path and extension)
   */
  std::string getFileName() const;

  /** \brief _fileName setter
   **   sets _fileName to file_name
   ** \param file_name Resource File Name to put into _fileName
   */
  void setFileName(std::string file_name);


  /** \brief _name getter
   ** \return _name : Resource alias
   **   _name could be an empty string
   */
  std::string getName() const;

  /** \brief _name setter
   **   sets _name to name
   ** \param name Resource alias name to put into _name
   */
  void setName(std::string name);


  /** \brief _id getter
   ** \return _id : Resource unique identifier
   */
  unsigned int getId() const;

  /** \brief _id setter
   **   sets _id to id
   ** \param id Resource Id to put into _id
   */
  void setid(unsigned int id);


protected:
  unsigned int _id; ///< unique Resource identifier
  std::string _fileName; ///< Resource file name (with full path and extension)
  std::string _name; ///< Resource alias name
  bool _loaded; ///< is the resource already in RAM ?
  e_scope _scope; ///< resource scope (the context it belongs to)
};

#endif /* !RESOURCE_HH_ */
