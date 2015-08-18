#include <game/Terrain.hh>


// // Terrain::Terrain(e_terrain terrain) :
//     _terrain(terrain),
//     _image (NULL)
// {
//   switch (_terrain)
//   {
//     case E_TERRAIN_FOREST:
//       _imageName = "forest";
//       break;

//     default:
//       std::cerr << "Unable to find Terrain Texture: " << _imageName << std::endl;
//   }
// }

// Image *Terrain::getImage()
// {
//   if (_image)
//     return _image;

//   // we never fetched it, let's do it now
//   switch (_terrain)
//   {
//     case E_TERRAIN_FOREST:
//       _image = GETIMAGE("forest");
//       break;

//     default:
//       std::cerr << "Unable to find Terrain Texture: " << _imageName << std::endl;
//       break;
//   }

//   return _image;
// }

// std::string Terrain::getImageName() {
//   return _imageName;
// }

// void Terrain::setImageName(std::string image_name)
// {
//   _imageName = image_name;
//   _image = GETIMAGE(image_name);
// }
