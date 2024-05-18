#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Bullet.hpp"

class Player : public Entity {
private:
  std::vector<Bullet> bullets;
  float attackSpeed;
  float fireRate;
  float fireRateTimer; // how much time has passed since the last shoot

  void initVariables();

public:
  Player(sf::Vector2f pos, sf::Texture* texture);
  ~Player();

  void updatePlayerPosition();
  void updateBullet(const float dt, const sf::Vector2f& target);
  void checkWindowCollision(const sf::Vector2u& windowSize);

  virtual void update(const float dt, sf::Window* window);
  virtual void render(sf::RenderTarget* target);
};

#endif