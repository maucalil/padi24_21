#include "Player.hpp"
#include <iostream>

void Player::initVariables()
{
  movSpeed = 4.f;
}

void Player::initSprite()
{
  if(!playerTexture.loadFromFile("../resources/player/dark_soldier-original.png")) {
    std::cout << "Error loading player texture!" << std::endl;
  } else {
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
  }
}

Player::Player(float x, float y)
{
  initVariables();
  initSprite();
  playerSprite.setPosition(x, y);
}

Player::~Player()
{
}

void Player::updatePlayerPosition()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    playerSprite.move(-movSpeed, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    playerSprite.move(movSpeed, 0.f);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    playerSprite.move(0.f, -movSpeed);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    playerSprite.move(0.f, movSpeed);
  } 
}

void Player::checkWindowCollision(const sf::RenderTarget *target)
{
  sf::Vector2u windowSize = target->getSize();
  
  if (playerSprite.getGlobalBounds().left <= 0.f) // Left
    playerSprite.setPosition(0.f, playerSprite.getGlobalBounds().top);
  
  if (playerSprite.getGlobalBounds().left + playerSprite.getGlobalBounds().width >= windowSize.x) // Right
    playerSprite.setPosition(windowSize.x - playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().top);

  if (playerSprite.getGlobalBounds().top <= 0.f) // Top
    playerSprite.setPosition(playerSprite.getGlobalBounds().left, 0.f);
  
  if (playerSprite.getGlobalBounds().top + playerSprite.getGlobalBounds().height >= windowSize.y) // Down
    playerSprite.setPosition(playerSprite.getGlobalBounds().left, windowSize.y - playerSprite.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
  updatePlayerPosition();
  checkWindowCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
  target->draw(playerSprite);
}
