#include "Player.hpp"
#include <iostream>

void Player::initVariables()
{
  movSpeed = 5.f;
}

Player::Player(sf::Vector2f pos, sf::Texture* texture)
{
  initVariables();

  createSprite(texture);
  sprite.setPosition(pos);
  sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

  std::cout << "Created Player\n";
}

Player::~Player()
{
  std::cout << "Destroyed Player\n";
}

void Player::updatePlayerPosition()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    sprite.move(-movSpeed, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    sprite.move(movSpeed, 0.f);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    sprite.move(0.f, -movSpeed);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    sprite.move(0.f, movSpeed);
  } 
}

void Player::checkWindowCollision(const sf::RenderTarget *target)
{
  sf::Vector2u windowSize = target->getSize();
  
  if (sprite.getGlobalBounds().left <= 0.f) // Left
    sprite.setPosition(0.f, sprite.getGlobalBounds().top);
  
  if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= windowSize.x) // Right
    sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);

  if (sprite.getGlobalBounds().top <= 0.f) // Top
    sprite.setPosition(sprite.getGlobalBounds().left, 0.f);
  
  if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >= windowSize.y) // Down
    sprite.setPosition(sprite.getGlobalBounds().left, windowSize.y - sprite.getGlobalBounds().height);
}

void Player::update(const float dt, sf::RenderTarget *target)
{
  updatePlayerPosition();
  checkWindowCollision(target);
}
