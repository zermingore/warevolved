/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 * \brief Terrain class definition
 */

#include <game/Terrain.hh>
#include <resources/ResourcesManager.hh>



Terrain::Terrain(int cover, const std::string& texture_name)
  : _cover(cover)
  , _textureName(texture_name)
{
  _texture = resources::ResourcesManager::getTexture(texture_name);
}


const std::string& Terrain::name() const
{
  return _textureName;
}
