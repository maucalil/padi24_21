#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

class Constants {
public:
    enum AttributeType {
      DAMAGE = 0,
      ATK_SPEED = 1,
      HEALTH = 2
    };

    static const unsigned TileWidth = 128; // pixels
    static const unsigned TileHeight = 128; // pixels
    static const unsigned MapWidth = 15;
    static const unsigned MapHeight = 9;

    static const unsigned NumPossibleEnemyPos = 8;

    static sf::Vector2f GetEnemySpawnPosition(int number);
};

#endif