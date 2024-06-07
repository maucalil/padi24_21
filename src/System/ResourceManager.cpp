#include "System/ResourceManager.hpp"
ResourceManager *ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
}

sf::Texture *ResourceManager::getTexture(std::string texName)
{
  auto &texMap = Instance().textures;
  auto pairFound = texMap.find(texName);

  // if texture already exists, just return it
  if (pairFound != texMap.end())
  {
    return &pairFound->second;
  }

  // create texture if it not exists
  auto &texture = texMap[texName];
  std::string filename = std::string("../resources/") + texName;
  texture.loadFromFile(filename);

  return &texture;
}

sf::Font *ResourceManager::getFont(std::string fontName)
{
  auto &fontMap = Instance().fonts;
  auto pairFound = fontMap.find(fontName);

  // if font already exists, just return it
  if (pairFound != fontMap.end())
  {
    return &pairFound->second;
  }

  // create font if it not exists
  auto &font = fontMap[fontName];
  std::string filename = std::string("../resources/") + fontName;
  font.loadFromFile(filename);

  return &font;
}
