#ifndef RESOURCE_HH_
# define RESOURCE_HH_

# include <common/include.hh>


// should split scopes ?
// (menu_scopes) with main, end game, network
enum e_scope
{
  E_SCOPE_MAIN_MENU,

  E_SCOPE_ANY_GAME, // in-game_menu, cursor
  E_SCOPE_SNOWY,
  E_SCOPE_SUNNY,

  E_SCOPE_ALL // the resource will be present in any scope
};


class Resource
{
public:
  Resource();
  virtual ~Resource();

  virtual bool load() = 0;
  virtual bool unload() = 0;

  std::string getFileName() const;
  void setFileName(std::string file_name);


protected:
  unsigned int _id;
  std::string _fileName;

  bool _loaded; ///< is the resource already in RAM ?
  e_scope _scope; ///< resource scope (the context it belongs to)
};

#endif /* !RESOURCE_HH_ */
