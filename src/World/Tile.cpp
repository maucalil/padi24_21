#include "World/Tile.hpp"

Tile::Tile(int tileNumber, sf::Vector2u mapPos, sf::Vector2u tilesheetPos, sf::Vertex *quad)
  : tileNumber(tileNumber)
{
  if (tileNumber == Constants::TileNumber::Sand || tileNumber == Constants::TileNumber::Grass)
    tileType = WALKABLE;
  else
    tileType = COLLIDABLE;

  tileBounds.left = mapPos.x * tileSize.x;
  tileBounds.top = mapPos.y * tileSize.y;
  tileBounds.width = (mapPos.x + 1) * tileSize.x - tileBounds.left;
  tileBounds.height = (mapPos.y + 1) * tileSize.y - tileBounds.top;

  // define its 4 corners
  quad[0].position = sf::Vector2f(tileBounds.left, tileBounds.top);
  quad[1].position = sf::Vector2f(tileBounds.left + tileBounds.width, tileBounds.top);
  quad[2].position = sf::Vector2f(tileBounds.left + tileBounds.width, tileBounds.top + tileBounds.height);
  quad[3].position = sf::Vector2f(tileBounds.left, tileBounds.top + tileBounds.height);

  // define its 4 texture coordinates
  quad[0].texCoords = sf::Vector2f(tilesheetPos.x * tileSize.x, tilesheetPos.y * tileSize.y);
  quad[1].texCoords = sf::Vector2f((tilesheetPos.x + 1) * tileSize.x, tilesheetPos.y * tileSize.y);
  quad[2].texCoords = sf::Vector2f((tilesheetPos.x + 1) * tileSize.x, (tilesheetPos.y + 1) * tileSize.y);
  quad[3].texCoords = sf::Vector2f(tilesheetPos.x * tileSize.x, (tilesheetPos.y + 1) * tileSize.y);
}

Tile::~Tile()
{
}

sf::IntRect Tile::getTileBounds()
{
  return tileBounds;
}

bool Tile::hasCollision()
{
  return tileType == COLLIDABLE;
}