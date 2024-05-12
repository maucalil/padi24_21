#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"

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

  // ----------------------- LOAD -----------------------
  // ----------------------- LOAD -----------------------

  while (game.isRunning())
  {
    // ----------------------- UPDATE -----------------------
    game.update();
    // ----------------------- UPDATE -----------------------

    // ----------------------- DRAW -----------------------
    game.render();
    // ----------------------- DRAW -----------------------
  }

  return 0;
}