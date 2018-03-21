#include <game/Terrain.hh>


Terrain::Terrain(int cover, std::shared_ptr<graphics::Texture> texture)
  : _cover(cover)
  , _texture(texture)
{
}
