#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Hitbox.hpp"

class Entity
{
protected:
  sf::Sprite sprite;
  Hitbox* hitbox;

  sf::Vector2f lastValidPosition;

  float movSpeed;
  int health;

  virtual void move(const float dt, const sf::Vector2f& dir);
  void createHitbox();

public:
  Hitbox& getHitbox();
  sf::Vector2f getPosition();
  int getHealth();

  void handleCollision();
  
  void update(const float dt, sf::Window* window);
  virtual void render(sf::RenderTarget* target) = 0;
};

#endif