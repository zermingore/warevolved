/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 * \brief Soldier (specific Unit) class declaration
 */

#ifndef SOLDIER_HH_
# define SOLDIER_HH_

# include <string>
# include <game/units/Unit.hh>



/**
 * \class Soldier
 * \brief Specialization of Unit class
 */
class Soldier: public Unit
{
public:
  /**
   * \brief Default Constructor. Initializes characteristics motion, hp, ...
   */
  Soldier();


  /**
   * \brief _minRange getter
   * \note If a weapon is equipped and usable, it's range will be considered
   * \return Minimal attack range (in Cells)
   */
  virtual size_t minRange() const final;

  /**
   * \brief Maximal attack / defense getter
   * \note If a weapon is equipped and usable, it's range will be considered
   * \return Maximal attack / defense range (in Cells)
   */
  virtual size_t maxRange() const final;
};

#endif /* !SOLDIER_HH_ */
