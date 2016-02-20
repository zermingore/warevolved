/*
 * game/items/Item.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef ITEM_HH_
# define ITEM_HH_

# include <resources/Image.hh>

/** \class Describes a generic Item, with a weight, image, ...
 */
class Item
{
public:
  /**
   * \brief _name getter
   * \return _name value
   */
  std::string name();

private:
  std::string _name; ///< item name
  // TODO option: change displayed units (kg / lbs, meter / miles)
  unsigned int _weight; ///< weight, in grams
  // Image *_image; ///< tooltip image
};

#endif /* !ITEM_HH_ */
