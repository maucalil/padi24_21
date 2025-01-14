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
    HEALTH = 2,
    MOV_SPEED = 3,
  };
  static constexpr float MaxFireRate = 0.1f;

  // Bullet
  static constexpr float DefaultBulletSpeed = 500.f;

  // Player
  static constexpr int DefaultPlayerDamage = 20;
  static constexpr float DefaultPlayerFireRate = 0.5f; // seconds - 2 attacks per second
  static constexpr int DefaultPlayerHealth = 140;
  static constexpr int DefaultPlayerExpNextLvl = 20;
  static constexpr float DefaultPlayerMovSpeed = 150.f;

  static constexpr unsigned PlayerIdleTextureWidth = 1252;
  static constexpr unsigned PlayerIdleTextureHeight = 1035;
  static constexpr unsigned PlayerIdleFrameWidth = 313;
  static constexpr unsigned PlayerIdleFrameHeight = 207;
  static constexpr unsigned PlayerIdleNumFrames = 20;
  static constexpr float PlayerIdleTimePerFrame = .1f;

  static constexpr unsigned PlayerMoveTextureWidth = 1252;
  static constexpr unsigned PlayerMoveTextureHeight = 1030;
  static constexpr unsigned PlayerMoveFrameWidth = 313;
  static constexpr unsigned PlayerMoveFrameHeight = 206;
  static constexpr unsigned PlayerMoveNumFrames = 20;
  static constexpr float PlayerMoveTimePerFrame = .05f;

  static constexpr unsigned PlayerShootTextureWidth = 936;
  static constexpr unsigned PlayerShootTextureHeight = 206;
  static constexpr unsigned PlayerShootFrameWidth = 312;
  static constexpr unsigned PlayerShootFrameHeight = 206;
  static constexpr unsigned PlayerShootNumFrames = 3;
  static constexpr float PlayerShootTimePerFrame = .15f;

  // Enemy
  static constexpr int DefaultEnemyDamage = 20;
  static constexpr int DefaultEnemyHealth = 40;
  static constexpr int DefaultEnemyExp = 7;
  static constexpr float DefaultEnemyMovSpeed = 100.f;
  static constexpr float DefaultEnemyAttackSpeed = 1.f; // 1 attack per second

  static constexpr unsigned EnemyMoveTextureWidth = 1152;
  static constexpr unsigned EnemyMoveTextureHeight = 1555;
  static constexpr unsigned EnemyMoveFrameWidth = 288;
  static constexpr unsigned EnemyMoveFrameHeight = 311;
  static constexpr unsigned EnemyMoveNumFrames = 17;
  static constexpr float EnemyMoveTimePerFrame = .075f;

  static constexpr unsigned EnemyAttackTextureWidth = 954;
  static constexpr unsigned EnemyAttackTextureHeight = 882;
  static constexpr unsigned EnemyAttackFrameWidth = 318;
  static constexpr unsigned EnemyAttackFrameHeight = 294;
  static constexpr unsigned EnemyAttackNumFrames = 9;
  static constexpr float EnemyAttackTimePerFrame = .12f;

  // Wave
  static constexpr int DefaultWaveNumEnemies = 10;

  static sf::Vector2f GetEnemySpawnPosition(int number);

  // Map
  static const unsigned TileWidth = 128;  // pixels
  static const unsigned TileHeight = 128; // pixels
  static const unsigned MapWidth = 15;
  static const unsigned MapHeight = 9;
  static const unsigned NumPossibleEnemyPos = 8;

  enum TileNumber
  {
    Sand,
    Beach_T_Grass_1,
    Beach_T_1,
    Beach_T_Grass_2,
    Beach_T_2,
    Beach_TL_Grass_1,
    Beach_TL_1,
    Beach_R_Grass_1,
    Grass,
    Beach_R_1,
    Beach_R_2,
    Beach_R_Grass_2,
    Beach_R_Grass_3,
    Beach_R_3,
    Beach_BR_Grass_1,
    Beach_BR_1,
    Beach_TR_Grass_1,
    Beach_R_Grass_4,
    Beach_TR_Grass_2,
    Beach_L_Grass_1,
    Beach_L_1,
    Beach_L_Grass_2,
    Beach_L_2,
    Beach_L_Grass_3,
    Beach_TR_1,
    Beach_R_4,
    Beach_TR_2,
    Beach_L_3,
    Beach_TL_Grass_2,
    Beach_TL_2,
    Beach_BR_Grass_2,
    Beach_BR_2,
    Beach_T_Grass_3,
    Beach_R_Grass_5,
    Beach_TR_Grass_3,
    Beach_L_Grass_4,
    Beach_B_Grass_1,
    Beach_B_Grass_2,
    Beach_B_1,
    Beach_B_Grass_3,
    Beach_T_4,
    Beach_R_5,
    Beach_TR_3,
    Beach_L_4,
    Beach_B_2,
    Beach_B_3,
    Beach_BL_Grass_1,
    Beach_BL_1,
    Beach_T_Grass_4,
    Beach_R_Grass_6,
    Beach_BR_Grass_3,
    Beach_TL_Grass_3,
    Beach_B_Grass_4,
    Beach_B_Grass_5,
    Water,
    Road_Up_D,
    Null_1,
    Beach_T_5,
    Beach_R_6,
    Beach_BR_3,
    Beach_TL_3,
    Beach_B_4,
    Beach_B_5,
    Road_Up,
    Road_Up_DT,
    Road_Horizontal_D,
    Road_Horizontal_DL,
    Road_Horizontal_DR,
    Road_Horizontal,
    Dirt_L,
    Dirt_R,
    Dirt_T,
    Road_Up_DB,
    Dirt_B,
  };
};

#endif