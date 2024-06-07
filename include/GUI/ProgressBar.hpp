#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "System/ResourceManager.hpp"

class ProgressBar
{
private:
  std::string barString;
  sf::Text text;
  float maxWidth;
  sf::RectangleShape back;
  sf::RectangleShape inner;

public:
  ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color inner_color);
  ~ProgressBar();
  
  //Functions
  void update(const int current_value, const int max_value);
  void render(sf::RenderTarget & target);
};

#endif