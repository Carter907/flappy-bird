#include "game.h"
#include <vector>
#include "bird.h"

void Game::restart(Bird *bird, std::vector<Rectangle> &pipes) {
    best_score = std::max(score, best_score);
    score = 0;
    bird->die();

    pipes.clear();

    for (int i = 0; i < MAX_PIPES; i++) {
        pipes.push_back(getRandomOpening(i));
    }
}

Rectangle getRandomOpening(int index) {
    return Rectangle{
        START_OFFSET + index * (float) PIPE_PADDING,
        (float) GetRandomValue(50, (SCREEN_HEIGHT - 80) - OPENING_HEIGHT),
        OPENING_WIDTH,
        OPENING_HEIGHT,
    };
}
