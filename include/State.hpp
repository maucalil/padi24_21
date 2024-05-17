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

  //Resources
	std::map<std::string, sf::Texture> textures;


public:
  State(sf::RenderWindow* window);
  virtual ~State();

  const bool& getQuit() const;

  virtual void updateInput() = 0;
  virtual void update(const float dt) = 0;
  virtual void render(sf::RenderTarget* target) = 0;
};

#endif