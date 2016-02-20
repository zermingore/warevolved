/*
 * game/items/guns/Rifle.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef RIFLE_HH_
# define RIFLE_HH_

# include <game/items/guns/Gun.hh>

/** \class Assault Rifle class
 * an assault rifle is a heavy, long, accurate gun
 * it uses clips, specific items can be mounted on it
 *   such as silencers, scopes, ...
 * it is deprecated in close combat (in buildings)
 */
class Rifle : public Gun
{
public:
  Rifle();
  ~Rifle();

// private:
//   unsigned short _clipSize; ///< maximum number of bullet in the clip
};

#endif /* !RIFLE_HH_ */
