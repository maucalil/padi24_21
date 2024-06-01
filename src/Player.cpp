#include "Player.hpp"

void Player::initVariables()
{
  movSpeed = 150.f;
  attackSpeed = 500.f;
  fireRate = .15f; // seconds
  fireRateTimer = 0;
}

Player::Player(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("player/dark_soldier-original.png"));
  sprite.setPosition(pos);
  sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

  std::cout << "Created Player\n";
}

Player::~Player()
{
  std::cout << "Destroyed Player\n";
}

sf::Vector2f Player::getPosition()
{
  return sprite.getPosition();
}

void Player::updatePlayerPosition(const float dt)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    sprite.move(-movSpeed * dt, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    sprite.move(movSpeed * dt, 0.f);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    sprite.move(0.f, -movSpeed * dt);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    sprite.move(0.f, movSpeed * dt);
  } 
}

void Player::updateBullet(const float dt, const sf::Vector2f& target)
{
  fireRateTimer += dt;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= fireRate) {
    Bullet bullet = Bullet(sprite.getPosition(), target, attackSpeed);
    bullets.push_back(bullet);

    fireRateTimer = 0;
  }

  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i].update(dt);
  }
}

void Player::checkWindowCollision(const sf::Vector2u& windowSize)
{  
  if (sprite.getGlobalBounds().left <= 0.f) // Left
    sprite.setPosition(0.f, sprite.getGlobalBounds().top);
  
  if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= windowSize.x) // Right
    sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);

  if (sprite.getGlobalBounds().top <= 0.f) // Top
    sprite.setPosition(sprite.getGlobalBounds().left, 0.f);
  
  if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >= windowSize.y) // Down
    sprite.setPosition(sprite.getGlobalBounds().left, windowSize.y - sprite.getGlobalBounds().height);
}

void Player::update(const float dt, sf::Window* window)
{
  updatePlayerPosition(dt);
  checkWindowCollision(window->getSize());

  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
  updateBullet(dt, mousePos);
}

void Player::render(sf::RenderTarget *target)
{
  target->draw(sprite);

  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i].render(target);
  }
}
