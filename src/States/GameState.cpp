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

  pauseMenu = new PauseMenu(window->getView().getSize(), window->getView().getSize() / 2.f);
}

void GameState::initSounds()
{
  backgroundSound.setBuffer(*ResourceManager::getSoundBuffer("sounds/wind.ogg"));
  backgroundSound.setVolume(30);
  backgroundSound.setLoop(true);
  backgroundSound.play();
}

void GameState::togglePause()
{
  paused = !paused;
}

GameState::GameState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
  const int tileMap[Constants::MapWidth * Constants::MapHeight] = {
     5, 32,  1,  3, 48,  1, 32,  1, 48,  1, 32, 16, 28, 34, -1,
    35,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 18, 51, 18, 34,
    23,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 11,
    35,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 17,
    23,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 33,
    35,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  7,
    19,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 11,
    46, 36, 52, 37, 39, 53, 53, 36, 52, 37, 39, 53, 53, 36, 30,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  };
  
  map = new Map();
  map->load(tileMap);

  const int roadMap[Constants::MapWidth * Constants::MapHeight] = {
    -1, -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 55, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 55, -1, -1, -1, -1, -1, -1, -1, -1,
    69, 65, 67, 66, 64, 64, 64, 64, 65, 66, 64, 64, 64, 64, 68,
    -1, -1, -1, -1, 55, -1, -1, -1, -1, -1, 55, -1, -1, -1, -1,
    -1, -1, -1, -1, 55, -1, -1, -1, -1, -1, 55, -1, -1, -1, -1,
    -1, -1, -1, -1, 63, -1, -1, -1, -1, -1, 63, -1, -1, -1, -1,
    -1, -1, -1, -1, 70, -1, -1, -1, -1, -1, 70, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  };
  map->load(roadMap);

  initEntities();
  initGUI();
  initSounds();
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

  backgroundSound.stop();
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
  
  sf::Vector2u playerMapPos = map->getPositionOnMap(sf::Vector2u(player->getPosition()));
  Tile tile = map->getTileAtPosition(playerMapPos);
  if (tile.hasCollision()) {
    return true;
  }

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
    if (enemy->haveAttacked()) {
      player->handleEnemyHit(enemy->getDamage());
      if (player->isDead()) {
        changeState(new GameOverState(window, states));
      }
    }

    return true;
  }

  sf::Vector2u enemyMapPos = map->getPositionOnMap(sf::Vector2u(enemy->getPosition()));
  Tile tile = map->getTileAtPosition(enemyMapPos);
  if (tile.hasCollision()) {
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
      togglePause();
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
    else if (!enemySpawner->isSpawning() && event.key.code == sf::Keyboard::R) {
      enemySpawner->startSpawning();
    } else if (paused) {
      pauseMenu->update(event.key.code);

      if (pauseMenu->quit())
        window->close();
      else if (pauseMenu->resume())
        paused = false;
    }
    break;

  default:
    break;
  }
}

void GameState::update(const float dt)
{
  if (paused)
    return;

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

  enemySpawner->update(dt, enemies, map->getRandomWalkableTilePos());
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

  if (states->top() != this)
    this->~GameState();
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

  if (paused) {
    pauseMenu->render(target);
  }
}
