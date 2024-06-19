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

  isShooting = false;
  playerState = IDLE;
}

void Player::initAnimations()
{
  Animation *idleAnimation = new Animation(sprite, sf::Vector2u(Constants::PlayerIdleTextureWidth, Constants::PlayerIdleTextureHeight),
                                           sf::Vector2u(Constants::PlayerIdleFrameWidth, Constants::PlayerIdleFrameHeight),
                                           Constants::PlayerIdleNumFrames,
                                           Constants::PlayerIdleTimePerFrame);
  idleAnimation->setRepeat(true);
  animations[PlayerState::IDLE] = idleAnimation;

  Animation *moveAnimation = new Animation(sprite, sf::Vector2u(Constants::PlayerMoveTextureWidth, Constants::PlayerMoveTextureHeight),
                                           sf::Vector2u(Constants::PlayerMoveFrameWidth, Constants::PlayerMoveFrameHeight),
                                           Constants::PlayerMoveNumFrames,
                                           Constants::PlayerMoveTimePerFrame);
  moveAnimation->setRepeat(true);
  animations[PlayerState::MOVING] = moveAnimation;

  Animation *shootAnimation = new Animation(sprite, sf::Vector2u(Constants::PlayerShootTextureWidth, Constants::PlayerShootTextureHeight),
                                            sf::Vector2u(Constants::PlayerShootFrameWidth, Constants::PlayerShootFrameHeight),
                                            Constants::PlayerShootNumFrames,
                                            Constants::PlayerShootTimePerFrame);
  shootAnimation->setRepeat(true);
  animations[PlayerState::SHOOTING] = shootAnimation;

  sprite.setTexture(*ResourceManager::getTexture("player/player_idle.png"));
  changeAnimation(*animations[PlayerState::IDLE]);
}

void Player::levelUp()
{
  level++;
  levelUpPoints++;
  experience -= expNextLevel;
  expNextLevel += 2;
  std::cout << "Leveled up! (" << level << ")\n";
}

Player::Player(sf::Vector2f pos)
{
  initVariables();
  initAnimations();

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

  case Constants::AttributeType::MOV_SPEED:
    movSpeed += 10.f;
    break;

  default:
    return;
  }

  levelUpPoints--;
}

void Player::handleEnemyHit(const int &damage)
{
  health -= damage;
}

void Player::lookToMouse(const sf::Vector2f &mousePos)
{
  lookingDirection = Utils::NormalizeVector(mousePos - getPosition());
  float angle = Utils::GetAngle(lookingDirection);
  rotate(angle - sprite.getRotation()); // rotate just what it need minding the actual rotation
}

void Player::changeState(PlayerState state)
{
  playerState = state;
}

void Player::updatePlayerPosition(const float dt)
{
  lastValidPosition = getPosition();
  sf::Vector2f dir = sf::Vector2f(0.f, 0.f);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    dir = sf::Vector2f(-1.f, 0.f);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    dir = sf::Vector2f(1.f, 0.f);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    dir += sf::Vector2f(0.f, -1.f);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    dir += sf::Vector2f(0.f, 1.f);
  }

  if (dir != sf::Vector2f(0.f, 0.f))
  {
    changeState(PlayerState::MOVING);
  }
  else
  {
    changeState(PlayerState::IDLE);
  }

  move(dt, dir);
}

void Player::updateBullet(const float dt, std::vector<Bullet *> &bullets)
{
  isShooting = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  fireRateTimer += dt;
  if (isShooting && fireRateTimer >= fireRate)
  {
    bullets.push_back(new Bullet(getPosition(), lookingDirection));

    fireRateTimer = 0;
  }
}

void Player::updateAnimation()
{
  if (playerState == SHOOTING)
  {
    if (!(lastState == SHOOTING))
    {
      sprite.setTexture(*ResourceManager::getTexture("player/player_shoot.png"));
      changeAnimation(*animations[PlayerState::SHOOTING]);
    }
  }
  else if (playerState == MOVING)
  {
    if (!(lastState == MOVING))
    {
      sprite.setTexture(*ResourceManager::getTexture("player/player_move.png"));
      changeAnimation(*animations[PlayerState::MOVING]);
    }
  }
  else
  {
    if (!(lastState == IDLE))
    {
      sprite.setTexture(*ResourceManager::getTexture("player/player_idle.png"));
      changeAnimation(*animations[PlayerState::IDLE]);
    }
  }
}

void Player::update(const float dt, sf::Vector2f mousePos, std::vector<Bullet *> &bullets)
{
  lastState = playerState;
  lookToMouse(mousePos);
  updatePlayerPosition(dt);
  updateBullet(dt, bullets);

  if (isShooting)
    changeState(PlayerState::SHOOTING);

  updateAnimation();
  currentAnimation->update(dt);
}

void Player::render(sf::RenderTarget &target)
{
  target.draw(sprite);
}
