#ifndef MAP_HPP
#define MAP_HPP

#include "System/ResourceManager.hpp"
#include "World/Tile.hpp"

class Map
{
private:
  const sf::Vector2u tileSize = sf::Vector2u(Constants::TileWidth, Constants::TileHeight);
  const sf::Vector2u mapSize = sf::Vector2u(Constants::MapWidth, Constants::MapHeight);

  std::vector<sf::VertexArray> layers;
  std::map<unsigned, Tile*> tilesArr;
  std::vector<unsigned> walkableTilesIndex;

public:
  Map();
  ~Map();

  sf::Vector2u getPositionOnMap(sf::Vector2u pos);
  Tile& getTileAtPosition(sf::Vector2u mapPos);
  sf::Vector2f getRandomWalkableTilePos();
  void load(const int *tiles);
  void render(sf::RenderTarget &target);
};
#endif
