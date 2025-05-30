#include "game.h"

void Game::reset() {}

Rectangle getRandomOpening(int index) {

  return Rectangle{
      START_OFFSET + index * (float)PIPE_PADDING,
      (float)GetRandomValue(50, (SCREEN_HEIGHT - 80) - OPENING_HEIGHT),
      OPENING_WIDTH,
      OPENING_HEIGHT,
  };
}
