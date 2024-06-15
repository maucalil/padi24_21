#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "System/ResourceManager.hpp"
#include "System/Utils.hpp"
#include "Constants.hpp"

class Entity
{
protected:
  sf::Sprite sprite;

  sf::Vector2f lastValidPosition;

  float movSpeed;
  int health;
  int maxHealth;

  virtual void move(const float dt, const sf::Vector2f &dir);

public:
  sf::Sprite getSprite();
  sf::Vector2f getPosition();
  sf::Vector2f getCenter();
  int getHealth();
  int getMaxHealth();
  bool isDead();

  void handleCollision();
  void rotate(const float &angle);

  void update(const float dt, sf::Window *window);
  virtual void render(sf::RenderTarget &target) = 0;
};

#endif