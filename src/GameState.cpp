#include "GameState.hpp"

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(400, 400));
  enemySpawner = new EnemySpawner();
}

GameState::GameState(sf::RenderWindow *window)
    : State(window)
{
  initEntities();
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

void GameState::updateInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    quit = true;
}

void GameState::update(const float dt)
{
  updateInput();

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
  player->render(target);
  for (size_t i = 0; i < bullets.size(); i++)
  {
    bullets[i]->render(target);
  }

  enemySpawner->render(target);
  for (size_t i = 0; i < enemies.size(); i++)
  {
    enemies[i]->render(target);
  }
}
