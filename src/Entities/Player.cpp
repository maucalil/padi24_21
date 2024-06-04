#include "Entities/Player.hpp"

void Player::initVariables()
{
  bulletSpeed = DEFAULT_BULLET_SPEED;

  damage = DEFAULT_PLAYER_DAMAGE;
  fireRate = DEFAULT_PLAYER_FIRE_RATE;
  health = DEFAULT_PLAYER_HEALTH;
  missingExp = DEFAULT_PLAYER_MISSING_EXP;
  movSpeed = DEFAULT_PLAYER_MOV_SPEED;

  fireRateTimer = 0;
  levelUpPoints = 0;
}

void Player::levelUp()
{
  levelUpPoints++;
  missingExp = DEFAULT_PLAYER_MISSING_EXP;
  std::cout << "Leveled up!\n";
}

Player::Player(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("player/player.png"));
  sprite.setTextureRect(sf::IntRect(37, 37, 259, 153));
  sprite.setOrigin(getCenter());
  sprite.setPosition(pos);
  sprite.scale(sf::Vector2f(0.5f, 0.5f));

  createHitbox();
}

Player::~Player()
{
  delete hitbox;
}

int Player::getDamage()
{
  return damage;
}

void Player::earnExp(const int &exp)
{
  missingExp -= exp;
  if (missingExp <= 0)
    levelUp();
    
  std::cout << "Missing exp: " << missingExp << std::endl;
}

void Player::lookToMouse(const sf::Vector2f &mousePos)
{
  lookingDirection = Utils::NormalizeVector(mousePos - getPosition());
  float angle = Utils::GetAngle(lookingDirection);
  rotate(angle - sprite.getRotation()); // rotate just what it need minding the actual rotation
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

void Player::updateBullet(const float dt, std::vector<Bullet*>& bullets)
{
  fireRateTimer += dt;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= fireRate) {
    bullets.push_back(new Bullet(getPosition(), lookingDirection, bulletSpeed));

    fireRateTimer = 0;
  }
}

void Player::update(const float dt, sf::Vector2f mousePos, std::vector<Bullet*>& bullets)
{
  updatePlayerPosition(dt);
  lookToMouse(mousePos);
  hitbox->update();

  updateBullet(dt, bullets);
}

void Player::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  hitbox->render(target);
}
