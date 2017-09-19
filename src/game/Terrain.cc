#include <game/Terrain.hh>


Terrain::Terrain(int defense, std::shared_ptr<const graphics::Texture> texture)
  : _defense(defense)
  , _texture(texture)
{
}
