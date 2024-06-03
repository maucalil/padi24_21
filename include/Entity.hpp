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
  void createHitbox(bool centered=false);

public:
  Hitbox& getHitbox();
  sf::Vector2f getPosition();
  sf::Vector2f getCenter();
  bool isDead();

  void handleCollision();
  void rotate(const float& angle);
  
  void update(const float dt, sf::Window* window);
  virtual void render(sf::RenderTarget* target) = 0;
};

#endif