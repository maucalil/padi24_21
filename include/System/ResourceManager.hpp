#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <SFML/Graphics.hpp>
#include <map>

class ResourceManager
{
private:
  static ResourceManager *instance;
  static ResourceManager& Instance()
  {
    if (instance == nullptr)
    {
      instance = new ResourceManager();
    }

    return *instance;
  }

  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Font> fonts;

  ResourceManager();

public:
  static sf::Texture* getTexture(std::string texName);
  static sf::Font* getFont(std::string fontName);
};

#endif