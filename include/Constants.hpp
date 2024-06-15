#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

class Constants
{
public:
  // Attributes
  enum AttributeType
  {
    DAMAGE = 0,
    ATK_SPEED = 1,
    HEALTH = 2
  };

  // Map
  static const unsigned TileWidth = 128;  // pixels
  static const unsigned TileHeight = 128; // pixels
  static const unsigned MapWidth = 15;
  static const unsigned MapHeight = 9;
  static const unsigned NumPossibleEnemyPos = 8;

  // Bullet
  static constexpr float DefaultBulletSpeed = 500.f;

  // Player
  static constexpr int DefaultPlayerDamage = 10;
  static constexpr float DefaultPlayerFireRate = 0.5f; // seconds - 2 attacks per second
  static constexpr int DefaultPlayerHealth = 100;
  static constexpr int DefaultPlayerExpNextLvl = 20;
  static constexpr float DefaultPlayerMovSpeed = 150.f;

  // Enemy
  static constexpr int DefaultEnemyDamage = 10;
  static constexpr int DefaultEnemyHealth = 20;
  static constexpr int DefaultEnemyExp = 5;
  static constexpr float DefaultEnemyMovSpeed = 100.f;
  static constexpr float DefaultEnemyAttackSpeed = 1.f; // 1 attack per second

  static sf::Vector2f GetEnemySpawnPosition(int number);
};

#endif