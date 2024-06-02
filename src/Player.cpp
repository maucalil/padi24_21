#include "Player.hpp"

void Player::initVariables()
{
  movSpeed = 150.f;
  bulletSpeed = 500.f;
  damage = 10;
  fireRate = .15f; // seconds
  fireRateTimer = 0;
}

Player::Player(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("player/rogues.png"));
  sprite.setPosition(pos);
  sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
  sprite.scale(sf::Vector2f(2, 2));

  createHitbox();

  std::cout << "Created Player\n";
}

Player::~Player()
{
  std::cout << "Destroyed Player\n";
}

int Player::getDamage()
{
  return damage;
}

void Player::updatePlayerPosition(const float dt)
{
  lastValidPosition = getPosition();
  sf::Vector2f dir = sf::Vector2f(0.f, 0.f);

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    dir = sf::Vector2f(-1.f, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    dir = sf::Vector2f(1.f, 0.f);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    dir += sf::Vector2f(0.f, -1.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    dir += sf::Vector2f(0.f, 1.f);
  }

  move(dt, dir);
}

void Player::updateBullet(const float dt, const sf::Vector2f& target, std::vector<Bullet*>& bullets)
{
  fireRateTimer += dt;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= fireRate) {
    bullets.push_back(new Bullet(sprite.getPosition(), target, bulletSpeed));

    fireRateTimer = 0;
  }
}

void Player::update(const float dt, sf::Window* window, std::vector<Bullet*>& bullets)
{
  updatePlayerPosition(dt);
  hitbox->update();

  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
  updateBullet(dt, mousePos, bullets);
}

void Player::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  hitbox->render(target);
}
