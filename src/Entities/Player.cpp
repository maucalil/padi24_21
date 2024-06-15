#include "Entities/Player.hpp"

void Player::initVariables()
{
  damage = Constants::DefaultPlayerDamage;
  fireRate = Constants::DefaultPlayerFireRate;
  health = Constants::DefaultPlayerHealth;
  maxHealth = Constants::DefaultPlayerHealth;
  expNextLevel = Constants::DefaultPlayerExpNextLvl;
  movSpeed = Constants::DefaultPlayerMovSpeed;

  experience = 0;
  fireRateTimer = 0;
  level = 1;
  levelUpPoints = 0;
}

void Player::levelUp()
{
  level++;
  levelUpPoints++;
  experience -=expNextLevel;
  expNextLevel += 2;
  std::cout << "Leveled up! (" << level << ")\n";
}

Player::Player(sf::Vector2f pos)
{
  initVariables();

  sprite.setTexture(*ResourceManager::getTexture("player/player.png"));
  sprite.setTextureRect(sf::IntRect(37, 37, 259, 153));
  sprite.setOrigin(getCenter());
  sprite.setPosition(pos);
  sprite.scale(sf::Vector2f(0.4f, 0.4f));
}

Player::~Player()
{
}

int Player::getDamage()
{
  return damage;
}

int Player::getExp()
{
  return experience;
}

int Player::getExpNextLevel()
{
  return expNextLevel;
}

std::vector<std::string> Player::getAttributesMap()
{
  std::vector<std::string> attributesMap;
  attributesMap.push_back("Level: " + std::to_string(level));
  attributesMap.push_back("Points: " + std::to_string(levelUpPoints));
  attributesMap.push_back("Damage: " + std::to_string(damage));
  attributesMap.push_back("Atk. Speed: " + std::to_string(fireRate));
  attributesMap.push_back("Mov. Speed: " + std::to_string(movSpeed));

  return attributesMap;
}

void Player::earnExp(const int &exp)
{
  experience += exp;
  if (experience >= expNextLevel)
    levelUp();
}

void Player::increaseAttribute(Constants::AttributeType attributeType)
{
  if (levelUpPoints == 0)
    return;

  switch (attributeType)
  {
  case Constants::AttributeType::DAMAGE:
    damage += 5;
    break;

  case Constants::AttributeType::ATK_SPEED:
    fireRate -= .025f;
    break;

  case Constants::AttributeType::HEALTH:
    maxHealth += 5;
    health = maxHealth;
    break;
  
  default:
    break;
  }

  levelUpPoints--;
  std::cout << "===== Stats =====\n";
  std::cout << "Damage: " << damage << std::endl;
  std::cout << "Atk Speed: " << fireRate << std::endl;
  std::cout << "Health: " << health << std::endl;
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
    bullets.push_back(new Bullet(getPosition(), lookingDirection));

    fireRateTimer = 0;
  }
}

void Player::update(const float dt, sf::Vector2f mousePos, std::vector<Bullet*>& bullets)
{
  updatePlayerPosition(dt);
  lookToMouse(mousePos);

  updateBullet(dt, bullets);
}

void Player::render(sf::RenderTarget &target)
{
  target.draw(sprite);
}
