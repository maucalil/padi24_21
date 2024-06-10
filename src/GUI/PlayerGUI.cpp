#include "GUI/PlayerGUI.hpp"


PlayerGUI::PlayerGUI(Player *player)
{
  this->player = player;

  sf::Vector2f hpBarPosition = sf::Vector2f(20, 20);
  sf::Vector2f hpBarSize = sf::Vector2f(400, 40);
  sf::Color hpBarColor = sf::Color(255, 0, 0, 220);
  hpBar = new ProgressBar(hpBarPosition, hpBarSize, hpBarColor);

  sf::Vector2f expBarPosition = sf::Vector2f(20, 80);
  sf::Vector2f expBarSize = sf::Vector2f(400, 40);
  sf::Color expBarColor = sf::Color(0, 255, 0, 220);
  expBar = new ProgressBar(expBarPosition, expBarSize, expBarColor);

  attributesContainer = new Container();
  attributesContainer->createLayout(30, sf::Vector2f(20.f, 20.f));
}

PlayerGUI::~PlayerGUI()
{
  delete hpBar;
  delete expBar;
  delete attributesContainer;
}

void PlayerGUI::update(const float &dt)
{
  hpBar->update(player->getHealth(), player->getMaxHealth());
  expBar->update(player->getExp(), player->getExpNextLevel());
  attributesContainer->update(player->getAttributesMap());
}

void PlayerGUI::render(sf::RenderTarget &target)
{
  hpBar->render(target);
  expBar->render(target);
  attributesContainer->render(target);
}
