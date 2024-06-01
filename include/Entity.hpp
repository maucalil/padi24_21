#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity
{
protected:
  sf::Sprite sprite;

  float movSpeed;
  unsigned health;

  virtual void move(const float dt, const sf::Vector2f& dir);

public:
  Entity();
  virtual ~Entity();

  void createSprite(sf::Texture* texture);

  void update(const float dt, sf::Window* window);
  virtual void render(sf::RenderTarget* target) = 0;
};

#endif