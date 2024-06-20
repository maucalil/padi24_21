#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Tile
{
private:
  enum TileType
  {
    WALKABLE,
    COLLIDABLE,
  };
  const sf::Vector2u tileSize = sf::Vector2u(Constants::TileWidth, Constants::TileHeight);

  int tileNumber;
  TileType tileType;
  sf::IntRect tileBounds;

public:
  Tile(int tileNumber, sf::Vector2u mapPos, sf::Vector2u tilesheetPos, sf::Vertex *quad);
  ~Tile();

  sf::IntRect getTileBounds();
  bool hasCollision();
};
#endif
