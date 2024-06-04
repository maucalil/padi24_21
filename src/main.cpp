#include <SFML/Audio.hpp>
#include "System/Game.hpp"

int main()
{
  // ----------------------- INITIALIZE -----------------------
  Game game;

  // Load a music to play
  sf::Music music;
  if (!music.openFromFile("../resources/sounds/nice_music.ogg"))
    return EXIT_FAILURE;

  // Play the music
  music.play();
  music.setVolume(0);
  music.setLoop(true);
  // ----------------------- INITIALIZE -----------------------
  
  game.run();

  return 0;
}