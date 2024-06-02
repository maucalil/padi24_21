#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Bullet.hpp"
#include "ResourceManager.hpp"

class Player : public Entity {
private:
  float bulletSpeed;
  int damage;
  float fireRate;
  float fireRateTimer; // how much time has passed since the last shoot

  void initVariables();

public:
  Player(sf::Vector2f pos);
  ~Player();

  int getDamage();

  void updatePlayerPosition(const float dt);
  void updateBullet(const float dt, const sf::Vector2f& target, std::vector<Bullet*>& bullets);

  virtual void update(const float dt, sf::Window* window, std::vector<Bullet*>& bullets);
  virtual void render(sf::RenderTarget* target);
};

#endif