#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/Entity.hpp"
#include "Entities/Bullet.hpp"

class Player : public Entity {
private:
  float fireRate;
  float fireRateTimer; // how much time has passed since the last shoot
  int damage;

  int experience;
  int expNextLevel; // how much experience is needed to the next level
  int level;
  int levelUpPoints;

  sf::Vector2f lookingDirection;

  void initVariables();
  void levelUp();

public:
  Player(sf::Vector2f pos);
  ~Player();

  int getDamage();
  int getExp();
  int getExpNextLevel();
  std::vector<std::string> getAttributesMap();

  void earnExp(const int& exp);
  void increaseAttribute(Constants::AttributeType attributeType);
  void handleEnemyHit(const int &damage);
  void lookToMouse(const sf::Vector2f& mousePos);

  void updatePlayerPosition(const float dt);
  void updateBullet(const float dt, std::vector<Bullet*>& bullets);

  virtual void update(const float dt, sf::Vector2f mousePos, std::vector<Bullet*>& bullets);
  virtual void render(sf::RenderTarget& target);
};

#endif