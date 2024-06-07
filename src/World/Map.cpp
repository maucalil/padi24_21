#include "World/Map.hpp"

Map::Map()
{
  const int firstLayerTiles[mapSize.x * mapSize.y] = {
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54
  };
  
  load(firstLayerTiles);
}

void Map::load(const int * tiles)
{
  sf::Texture* tilesheet = ResourceManager::getTexture("world/tilesheet.png");
  
  // resize the vertex array to fit the level size
  sf::VertexArray layer;
  layer.setPrimitiveType(sf::Quads);
  layer.resize(mapSize.x * mapSize.y * 4);

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < mapSize.x; ++i)
  {
    for (unsigned int j = 0; j < mapSize.y; ++j)
    {
      // get the current tile number
      int tileNumber = tiles[i + j * mapSize.x];

      // if nothing want to be draw on that position
      if (tileNumber == -1) continue;

      // find its position in the tileset texture
      int tu = tileNumber % (tilesheet->getSize().x / tileSize.x);
      int tv = tileNumber / (tilesheet->getSize().x / tileSize.x);

      // get a pointer to the current tile's quad
      sf::Vertex *quad = &layer[(i + j * mapSize.x) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }

  layers.push_back(layer);
}

void Map::render(sf::RenderTarget *target)
{
  sf::Texture* tilesheet = ResourceManager::getTexture("world/tilesheet.png");

  for (sf::VertexArray layer : layers) {
    target->draw(layer, tilesheet);
  }
}
