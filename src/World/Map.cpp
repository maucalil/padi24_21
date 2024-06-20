#include "World/Map.hpp"

Map::Map()
{
  srand(time(0));
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

Map::~Map()
{
}

sf::Vector2u Map::getPositionOnMap(sf::Vector2u pos)
{
  return sf::Vector2u(pos.x / tileSize.x, pos.y / tileSize.y);
}

Tile &Map::getTileAtPosition(sf::Vector2u mapPos)
{
  unsigned index = mapPos.x + mapPos.y * mapSize.x;

  return *tilesArr.at(index);
}

sf::Vector2f Map::getRandomWalkableTilePos()
{
  unsigned index = rand() % walkableTilesIndex.size();

  sf::IntRect tileBounds = tilesArr[walkableTilesIndex[index]]->getTileBounds();
  sf::Vector2f tileCenter(tileBounds.left + tileBounds.width / 2, tileBounds.top + tileBounds.height / 2);

  return tileCenter;
}

void Map::load(const int *tiles)
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
      sf::Vector2u mapPos(i, j);
      sf::Vector2u tilesheetPos(tu, tv);
      Tile* tile = new Tile(tileNumber, mapPos, tilesheetPos, quad);
      tilesArr[i + j * mapSize.x] = tile;

      if (!tile->hasCollision())
        walkableTilesIndex.push_back(i + j * mapSize.x);
    }
  }

  layers.push_back(layer);
}

void Map::render(sf::RenderTarget &target)
{
  sf::Texture* tilesheet = ResourceManager::getTexture("world/tilesheet.png");

  for (sf::VertexArray layer : layers) {
    target.draw(layer, tilesheet);
  }
}
