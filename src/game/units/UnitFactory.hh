/**
 * \file
 * \date February 9, 2017
 * \author Zermingore
 * \brief UnitFactory declaration: Unit creation
 */

#ifndef UNIT_FACTORY_HH_
# define UNIT_FACTORY_HH_

# include <memory>
# include <common/enums/units.hh>

class Unit;


/// \todo investigate std::variant, could make things safer


/**
 * \class Unitfactory
 * \brief Unit creation, using the factory design pattern
 */
class UnitFactory
{
public:
  /**
   * \brief Creates a specialized Unit based on the given name
   * \param unit Unit type to create
   * \return a pointer to the freshly created Unit,
   *   nullptr if the name was invalid
   */
  static std::unique_ptr<Unit> createUnit(const e_unit& unit);

  /**
   * \brief Get the maximal number of HP for the given Unit type
   * \param type Unit type to get max HP
   * \return Maximal health points for the given type
   */
  static int typeMaxHp(const e_unit& type);
};

#endif /* !UNIT_FACTORY_HH_ */
