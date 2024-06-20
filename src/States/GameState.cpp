#include "States/GameState.hpp"

std::string GameState::getWaveText()
{
  std::string wave = std::to_string(enemySpawner->getWave());
  std::string killCounter = std::to_string(enemySpawner->getWaveNumEnemies() - enemySpawner->getRemainingEnemies());
  std::string waveNumEnemies = std::to_string(enemySpawner->getWaveNumEnemies());

  return "Wave " + wave + " (" + killCounter + "/" + waveNumEnemies + ")";
}

void GameState::initEntities()
{
  player = new Player(sf::Vector2f(960, 540));
  enemySpawner = new EnemySpawner();
}

void GameState::initGUI()
{
  playerGUI = new PlayerGUI(player);

  waveInfo.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
  waveInfo.setString(getWaveText());

  sf::FloatRect waveInfoBounds = waveInfo.getGlobalBounds();
  waveInfo.setOrigin(waveInfoBounds.left + waveInfoBounds.width / 2, waveInfoBounds.top + waveInfoBounds.height / 2);

  waveInfo.setPosition(window->getView().getSize().x / 2.f, 30.f);
}

GameState::GameState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
  const int tileMap[Constants::MapWidth * Constants::MapHeight] = {
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

  initEntities();
  initGUI();
}

GameState::~GameState()
{
  delete map;

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

  delete playerGUI;
}

bool GameState::checkWindowCollision(const sf::Sprite &sprite)
{
  sf::FloatRect spriteBounds = sprite.getGlobalBounds();

  if (spriteBounds.left <= 0.f) // Left
    return true;

  if (spriteBounds.left + spriteBounds.width >= window->getSize().x) // Right
    return true;

  if (spriteBounds.top <= 0.f) // Top
    return true;

  if (spriteBounds.top + spriteBounds.height >= window->getSize().y) // Down
    return true;

  return false;
}

bool GameState::didPlayerCollide()
{
  // If player collides with window borders
  if (checkWindowCollision(player->getSprite()))
    return true;

  return false;
}

bool GameState::didEnemyCollide(Enemy *enemy, int enemyId)
{
  // If enemy collides with window borders
  if (checkWindowCollision(enemy->getSprite()))
    return true;

  // If enemy collides with player
  if (Collision::PixelPerfectTest(enemy->getSprite(), player->getSprite()))
  {
    enemy->setIsAttacking(true);
    if (enemy->haveAttacked())
      player->handleEnemyHit(enemy->getDamage());

    return true;
  }

  return false;
}

bool GameState::didBulletCollide(Bullet &bullet)
{
  // If bullet collide with window borders
  if (checkWindowCollision(bullet.getSprite()))
    return true;

  for (size_t i = 0; i < enemies.size(); i++)
  {
    // If bullet collides with an enemy
    if (Collision::PixelPerfectTest(bullet.getSprite(), enemies[i]->getSprite()))
    {
      enemies[i]->handleBulletHit(player->getDamage());

      if (enemies[i]->isDead())
      {
        player->earnExp(enemies[i]->getExp());
        delete enemies[i];
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
        enemySpawner->handleEnemyKilled();
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
    if (event.key.code == sf::Keyboard::Escape)
    {
      window->close();
    }
    else if (event.key.code == sf::Keyboard::Num1)
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
    else if (event.key.code == sf::Keyboard::Num4)
    {
      player->increaseAttribute(Constants::MOV_SPEED);
    }
    else if (!enemySpawner->isSpawning() && event.key.code == sf::Keyboard::R) {
      enemySpawner->startSpawning();
    }
    break;

  default:
    break;
  }
}

void GameState::update(const float dt)
{
  sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

  // Entities
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

  // GUI
  playerGUI->update(dt);
  waveInfo.setString(getWaveText());
}

void GameState::render(sf::RenderTarget &target)
{
  // Map
  map->render(target);

  // Entities
  player->render(target);
  for (size_t i = 0; i < bullets.size(); i++)
  {
    bullets[i]->render(target);
  }

  for (size_t i = 0; i < enemies.size(); i++)
  {
    enemies[i]->render(target);
  }

  // GUI
  playerGUI->render(target);
  target.draw(waveInfo);
}
