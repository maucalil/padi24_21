#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Entity.hpp"
#include "Entities/Bullet.hpp"

#define DEFAULT_BULLET_SPEED 500.f
#define DEFAULT_PLAYER_DAMAGE 10
#define DEFAULT_PLAYER_FIRE_RATE .15f // seconds
#define DEFAULT_PLAYER_HEALTH 100
#define DEFAULT_PLAYER_MISSING_EXP 20
#define DEFAULT_PLAYER_MOV_SPEED 150.f

class Player : public Entity {
private:
  float bulletSpeed;
  float fireRate;
  float fireRateTimer; // how much time has passed since the last shoot
  int damage;
  int levelUpPoints;
  int missingExp; // how much experience is needed to the next level

  sf::Vector2f lookingDirection;

  void initVariables();
  void levelUp();

public:
  Player(sf::Vector2f pos);
  ~Player();

  int getDamage();

  void earnExp(const int& exp);
  void lookToMouse(const sf::Vector2f& mousePos);

  void updatePlayerPosition(const float dt);
  void updateBullet(const float dt, std::vector<Bullet*>& bullets);

  virtual void update(const float dt, sf::Vector2f mousePos, std::vector<Bullet*>& bullets);
  virtual void render(sf::RenderTarget* target);
};

#endif