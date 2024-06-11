#include "Constants.hpp"

sf::Vector2f Constants::GetEnemySpawnPosition(int number)
{
  sf::Vector2f pos;
  switch (number)
  {
  case 0:
    pos = sf::Vector2f(200.f, 200.f);
    break;
  case 1:
    pos = sf::Vector2f(210.f, 935.f);
    break;
  case 2:
    pos = sf::Vector2f(675.f, 940.f);
    break;
  case 3:
    pos = sf::Vector2f(755.f, 220.f);
    break;
  case 4:
    pos = sf::Vector2f(1280.f, 330.f);
    break;
  case 5:
    pos = sf::Vector2f(1340.f, 940.f);
    break;
  case 6:
    pos = sf::Vector2f(1700.f, 455.f);
    break;
  case 7:
    pos = sf::Vector2f(1700.f, 935.f);
    break;
  
  default:
    break;
  }

  return pos;
}