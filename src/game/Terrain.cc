#include <game/Terrain.hh>
#include <iostream>



Terrain::Terrain() {
}


Terrain::Terrain(e_terrains terrain, ResourcesManager *rm) :
  _terrain (terrain),
  _textureId (0),
  _rm (rm)
{
}

Terrain::Terrain(e_terrains terrain) :
  _terrain (terrain),
  _textureId (0)
{
}

Terrain::~Terrain() {
}

unsigned int Terrain::getTextureId()
{
  if (_textureId)
	return _textureId;

  // we never fetched it, let's do it now
  switch (_terrain)
  {
	// case E_TERRAINS_FOREST:
	//   _textureId = _rm->getResourceId("texture_terrain_forest"); // TODO getImageId()

	default:
	  std::cerr <<
		"Unable to find Terrain Texture with id: " <<
		_textureId << std::endl;
  }
}

void Terrain::setTextureId(unsigned int texture_id) {
  _textureId = texture_id;
}
