#include "System/Animation.hpp"

Animation::Animation(sf::Sprite &sprite, sf::Texture *texture, sf::Vector2u frameSize, unsigned numFrames, float switchTime)
  : sprite(sprite), frameSize(frameSize), numFrames(numFrames), switchTime(switchTime)
{
  textureBounds = sf::Vector2u(texture->getSize());
  textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
  sprite.setTexture(*texture);
  sprite.setTextureRect(textureRect);

  currentFrame = 0;
}

void Animation::setRepeat(bool repeat)
{
  this->repeat = repeat;
}

void Animation::update(const float dt)
{
  elapsedTime += dt;

  // Perform the next frame if the time to switch has already passed
  // and if there are still frames left or repeat is true
  if (elapsedTime >= switchTime && (currentFrame <= numFrames || repeat))
  {
    elapsedTime -= switchTime; // smoothier animation
    textureRect.left += textureRect.width;

    if (textureRect.left + textureRect.width > textureBounds.x)
    {
      textureRect.left = 0;
      textureRect.top += textureRect.height;
    }

    if (repeat)
    {
      currentFrame = (currentFrame + 1) % numFrames;

      if (currentFrame == 0)
        textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
    }
    else
    {
      currentFrame++;
    }

    sprite.setTextureRect(textureRect);
  }
}
