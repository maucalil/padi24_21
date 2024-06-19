#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Animation
{
private:
  sf::Sprite& sprite;
  sf::Vector2u textureBounds;
  sf::IntRect textureRect;

  sf::Vector2u frameSize;
  unsigned numFrames;
  unsigned currentFrame;

  float elapsedTime;
  float switchTime;

  bool repeat;

public:
  Animation(sf::Sprite& sprite, sf::Vector2u textureBounds, sf::Vector2u frameSize, unsigned numFrames, float switchTime);
  ~Animation();

  void setRepeat(bool repeat);

  void restart();
  void update(const float dt);
};

#endif