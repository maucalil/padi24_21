#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

class Constants {
public:
    enum AttributeType {
      DAMAGE = 0,
      ATK_SPEED = 1,
      HEALTH = 2
    };

    static const unsigned int TileWidth = 128; // pixels
    static const unsigned int TileHeight = 128; // pixels
    static const unsigned int MapWidth = 15;
    static const unsigned int MapHeight = 9;

};

#endif