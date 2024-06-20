#include "System/Animation.hpp"

Animation::Animation(sf::Sprite &sprite, sf::Vector2u textureBounds, sf::Vector2u frameSize, unsigned numFrames, float switchTime)
  : sprite(sprite), frameSize(frameSize), numFrames(numFrames), switchTime(switchTime)
{
  this->textureBounds = textureBounds;
  textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
  sprite.setTextureRect(textureRect);

  currentFrame = 0;
  elapsedTime = 0.f;
  
}

void Animation::setRepeat(bool repeat)
{
  this->repeat = repeat;
}

void Animation::restart()
{
  textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
  sprite.setTextureRect(textureRect);

  currentFrame = 0;
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

      if (currentFrame == 0) {
        textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
      }
    }
    else
    {
      currentFrame++;
    }

    sprite.setTextureRect(textureRect);
  }
}
