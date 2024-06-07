#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Hitbox
{
private:
  sf::RectangleShape hitbox;
  sf::Vector2f size;
  sf::Sprite& sprite;

public:
  Hitbox(sf::Sprite& sprite);

  sf::FloatRect getHitboxBounds();
  bool checkCollision(const sf::FloatRect& frect);
  void rotate(const float& angle);

	void update();
  void render(sf::RenderTarget& target);
};

#endif