#include "States/GameState.hpp"

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(400, 400));
  enemySpawner = new EnemySpawner();
}

GameState::GameState(sf::RenderWindow *window)
    : State(window)
{
  initEntities();
  const int tileMap[15*9] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  5, 16, -1, -1,
    -1,  5, 32,  1,  3, 48,  1, 32,  1, 16, 28, 51, 18, 34, -1,
    -1, 23,  8,  8,  8,  8,  8,  8,  8, 18, 51,  8,  8, 11, -1,
    -1, 35,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 17, -1,
    -1, 23,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 33, -1,
    -1, 35,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  7, -1,
    -1, 19,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 11, -1,
    -1, 46, 36, 52, 37, 39, 53, 53, 36, 52, 37, 39, 53, 30, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  };

  map = new Map();
  map->load(tileMap);
}

GameState::~GameState()
{
  delete player;
  for (Bullet *bullet : bullets)
  {
    delete bullet;
  }

  delete enemySpawner;
  for (Enemy *enemy : enemies)
  {
    delete enemy;
  }
}

bool GameState::checkWindowCollision(Entity &entity)
{
  sf::FloatRect entityHitbox = entity.getHitbox().getHitboxBounds();

  if (entityHitbox.left <= 0.f) // Left
    return true;

  if (entityHitbox.left + entityHitbox.width >= window->getSize().x) // Right
    return true;

  if (entityHitbox.top <= 0.f) // Top
    return true;

  if (entityHitbox.top + entityHitbox.height >= window->getSize().y) // Down
    return true;

  return false;
}

bool GameState::didPlayerCollide()
{
  // If player collides with window borders
  if (checkWindowCollision(*player))
    return true;

  // Hitbox playerHitbox = player->getHitbox();

  // for (Enemy *enemy : enemies)
  // {
  //   if (playerHitbox.checkCollision(enemy->getHitbox().getHitboxBounds()))
  //     return true;
  // }

  return false;
}

bool GameState::didEnemyCollide(Enemy *enemy, int enemyId)
{
  // If enemy collides with window borders
  if (checkWindowCollision(*enemy))
    return true;

  Hitbox enemyHitbox = enemy->getHitbox();

  // If enemy collides with player
  if (enemyHitbox.checkCollision(player->getHitbox().getHitboxBounds()))
    return true;

  // for (int i = 0; i < enemies.size(); i++)
  // {
  //   // If enemy collides with another enemy
  //   if (i != enemyId && enemyHitbox.checkCollision(enemies[i]->getHitbox().getHitboxBounds()))
  //     return true;
  // }

  return false;
}

bool GameState::didBulletCollide(Bullet &bullet)
{
  // If bullet collide with window borders
  if (checkWindowCollision(bullet))
    return true;

  Hitbox bulletHitbox = bullet.getHitbox();
  for (size_t i = 0; i < enemies.size(); i++)
  {
    // If bullet collides with an enemy
    if (bulletHitbox.checkCollision(enemies[i]->getHitbox().getHitboxBounds()))
    {
      enemies[i]->handleBulletHit(player->getDamage());

      if (enemies[i]->isDead())
      {
        player->earnExp(enemies[i]->getExp());
        delete enemies[i];
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
      }

      return true;
    }
  }

  return false;
}

void GameState::handleEvent(const sf::Event &event)
{
  switch (event.type)
  {
  case sf::Event::KeyReleased:
    if (event.key.code == sf::Keyboard::Num1)
    {
      player->increaseAttribute(Constants::DAMAGE);
    }
    else if (event.key.code == sf::Keyboard::Num2)
    {
      player->increaseAttribute(Constants::ATK_SPEED);
    }
    else if (event.key.code == sf::Keyboard::Num3)
    {
      player->increaseAttribute(Constants::HEALTH);
    }
    break;

  default:
    break;
  }
}

void GameState::update(const float dt)
{
  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
  player->update(dt, mousePos, bullets);
  if (didPlayerCollide())
  {
    player->handleCollision();
  }

  for (size_t i = 0; i < bullets.size(); i++)
  {
    bullets[i]->update(dt);

    if (didBulletCollide(*bullets[i]))
    {
      delete bullets[i];
      bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]), bullets.end());
    }
  }

  enemySpawner->update(dt, enemies);
  for (int i = 0; i < enemies.size(); i++)
  {
    enemies[i]->update(dt, player->getPosition());

    if (didEnemyCollide(enemies[i], i))
    {
      enemies[i]->handleCollision();
    }
  }
}

void GameState::render(sf::RenderTarget *target)
{
  map->render(target);
  player->render(target);
  for (size_t i = 0; i < bullets.size(); i++)
  {
    bullets[i]->render(target);
  }

  // enemySpawner->render(target);
  for (size_t i = 0; i < enemies.size(); i++)
  {
    enemies[i]->render(target);
  }
}
