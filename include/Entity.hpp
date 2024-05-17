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

  virtual void move(const float dt, const sf::Vector2f& dir);

public:
  Entity();
  virtual ~Entity();

  void createSprite(sf::Texture* texture);

  virtual void update(const float dt, sf::RenderTarget *target) = 0;
  virtual void render(sf::RenderTarget* target);
};

#endif