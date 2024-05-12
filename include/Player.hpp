#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
private:
  sf::Texture playerTexture;
  sf::Sprite playerSprite;
  float movSpeed;

  void initVariables();
  void initSprite();

public:
  Player(float x = 0.f, float y = 0.f);
  ~Player();
  void updatePlayerPosition();
  void checkWindowCollision(const sf::RenderTarget* target);
  void update(const sf::RenderTarget* target);
  void render(sf::RenderTarget* target);
};

#endif