#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stack>
#include <map>
#include <iostream>

class State
{
protected:
  sf::RenderWindow* window;
  bool quit;

public:
  State(sf::RenderWindow* window);
  virtual ~State();

  const bool& getQuit() const;

  virtual void handleEvent(const sf::Event& event) = 0;
  virtual void update(const float dt) = 0;
  virtual void render(sf::RenderTarget* target) = 0;
};

#endif