#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "System/ResourceManager.hpp"
#include "Constants.hpp"

class Map
{
private:
  const sf::Vector2u tileSize = sf::Vector2u(Constants::TileWidth, Constants::TileHeight);
  const sf::Vector2u mapSize = sf::Vector2u(Constants::MapWidth, Constants::MapHeight);

  std::vector<sf::VertexArray> layers;

public:
  Map();
  ~Map();

  void load(const int *tiles);
  void render(sf::RenderTarget &target);
};
#endif
