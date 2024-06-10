#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "System/ResourceManager.hpp"

class Container
{
private:
  sf::RectangleShape container;
  sf::Vector2f size;
  sf::Vector2f position;

  std::vector<sf::Text> contents;

public:
  Container();

  void createLayout(const int& rowSize, const sf::Vector2f& padding);
  
  void update(const std::vector<std::string>& values);
  void render(sf::RenderTarget & target);
};

#endif