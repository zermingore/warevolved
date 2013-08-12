/*
 * game/items/guns/Gun.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef GUN_HH_
# define GUN_HH_

/** \class firearm class
 */
class Gun
{
public:
  Gun();
  virtual ~Gun();

  unsigned int getRange();

protected:
  unsigned int _range; ///< maximal range (in cells)
};

#endif /* !GUN_HH_ */
