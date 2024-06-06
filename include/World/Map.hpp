#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "System/ResourceManager.hpp"

class Map
{
private:
  sf::VertexArray vertices;

public:
  Map();
  ~Map();

  void load(sf::Vector2u tileSize, const int *tiles, unsigned int width, unsigned int height);
  void render(sf::RenderTarget* target);
};
#endif
