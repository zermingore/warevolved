/*
 * common/Text.hh
 *
 *  Created on: August 9, 2013
 *      Author: Zermingore
 */

#ifndef TEXT_HH_
# define TEXT_HH_

# include <map>
# include <string>
# include <interface/menus/MenuEntry.hh>
# include <common/enums/ranks.hh>
# include <common/enums/terrains.hh>


// TODO db
// static ? 2 different languages at same time on the same computer
/** \class Static class which role is to fetch the required text
 */
class Text
{
  public:
  /** \brief Constructor
   ** \param language database language column offset
   ** default value: English (offset = 0)
   */
  explicit Text(unsigned int language = 0);

  /** \brief fills in std::maps
   ** TODO initialize DataBase connection
   */
  void init();

  /** \brief return _name entry number id
   ** if id is not given, a random name is returned
   */
  std::string getName(int id = -1);

  /** \brief military rank text getter
   ** \param rank to fetch
   ** \return rank text
   */
  static std::string name(e_rank rank);
  static std::string name(e_terrain terrain);

  //  template <typename T>
  //  static std::string name(T id);

  /** \brief rank name getter
   ** \param rank rank we want name
   ** \return rank name value
   */
  inline std::string getRankName(e_rank rank) { return _ranks[rank]; }


private:
  unsigned int _language; ///< database language column offset value
  std::map<e_rank, std::string> _ranks; ///< military ranks names
  std::map<e_entry, std::string> _entries; ///< menu entries names
  std::vector<std::string> _names; ///< vector of built-in names (TODO DB)
};

#endif /* !TEXT_HH_ */
