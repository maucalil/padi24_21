#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <SFML/Graphics.hpp>

class Hitbox
{
private:
  sf::RectangleShape hitbox;
  sf::Vector2f offset;
  sf::Sprite& sprite;

public:
  Hitbox(sf::Sprite& sprite);

  sf::FloatRect getHitboxBounds();
  bool checkCollision(const sf::FloatRect& frect);

	void update();
  void render(sf::RenderTarget* target);
};

#endif