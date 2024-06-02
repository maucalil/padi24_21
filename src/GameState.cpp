#include "GameState.hpp"

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(2, 2));
  enemySpawner = new EnemySpawner();
}

GameState::GameState(sf::RenderWindow *window)
    : State(window)
{
  initEntities();

  std::cout << "Created GameState\n";
}

GameState::~GameState()
{
  delete player;
  for (Bullet* bullet : bullets) {
    delete bullet;
  }

  delete enemySpawner;
  for (Enemy* enemy : enemies) {
    delete enemy;
  }

  std::cout << "Destroyed GameState\n";
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
  Hitbox playerHitbox = player->getHitbox();

  bool didPlayerCollideWithEnemy = false;
  // for (Enemy *enemy : enemies)
  // {
  //   didPlayerCollideWithEnemy = playerHitbox.checkCollision(enemy->getHitbox().getHitboxBounds());

  //   if (didPlayerCollideWithEnemy)
  //   {
  //     break;
  //   }
  // }

  bool didPlayerCollideWithWindow = checkWindowCollision(*player);

  return didPlayerCollideWithEnemy || didPlayerCollideWithWindow;
}

bool GameState::didEnemyCollide(Enemy *enemy, int enemyId)
{
  Hitbox enemyHitbox = enemy->getHitbox();

  bool didEnemyCollideWithPlayer = enemyHitbox.checkCollision(player->getHitbox().getHitboxBounds());
  bool didEnemyCollideWithWindow = checkWindowCollision(*enemy);

  bool didEnemyCollideWithEnemy = false;
  // for (int i=0; i < enemies.size(); i++)
  // {
  //   if (i != enemyId) {
  //     didEnemyCollideWithEnemy = enemyHitbox.checkCollision(enemies[i]->getHitbox().getHitboxBounds());

  //     if (didEnemyCollideWithEnemy)
  //     {
  //       break;
  //     }
  //   }
  // }

  return didEnemyCollideWithPlayer || didEnemyCollideWithWindow || didEnemyCollideWithEnemy;
}

bool GameState::didBulletCollide(Bullet &bullet)
{
  Hitbox bulletHitbox = bullet.getHitbox();

  bool didBulletCollideWithEnemy = false;
  for (size_t i=0; i < enemies.size(); i++) {
    didBulletCollideWithEnemy = bulletHitbox.checkCollision(enemies[i]->getHitbox().getHitboxBounds());

    if (didBulletCollideWithEnemy) {
      enemies[i]->handleBulletHit(player->getDamage());
      if (enemies[i]->getHealth()) {
        delete enemies[i];
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
      }
      break;
    }
  }

  return didBulletCollideWithEnemy;
}

void GameState::updateInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    quit = true;
}

void GameState::update(const float dt)
{
  updateInput();

  player->update(dt, window, bullets);
  if (didPlayerCollide())
  {
    player->handleCollision();
  }

  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i]->update(dt);

    if (didBulletCollide(*bullets[i])) {
      delete bullets[i];
      bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]), bullets.end());
      
    }
  }

  enemySpawner->update(dt, enemies);
  for (int i=0; i < enemies.size(); i++)
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
  for (size_t i = 0; i < bullets.size(); i++) {
    bullets[i]->render(target);
  }

  enemySpawner->render(target);
  for (size_t i = 0; i < enemies.size(); i++)
  {
    enemies[i]->render(target);
  }

}
