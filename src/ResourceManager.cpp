#include "ResourceManager.hpp"

ResourceManager *ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() {

}

sf::Texture* ResourceManager::getTexture(std::string texName)
{
  auto& texMap = Instance().textures;
  auto pairFound = texMap.find(texName);

  // if texture already exists, just return it
  if (pairFound != texMap.end()) {
    return &pairFound->second;
  }

  // create texture if it not exists
  auto& texture = texMap[texName];
  std::string filename = std::string("../resources/") + texName;
  texture.loadFromFile(filename);

  return &texture;
}
