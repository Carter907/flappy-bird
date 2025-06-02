#include "game.h"
#include "pipe.h"
#include "bird.h"

void Game::restart(Bird& bird, std::deque<Pipe> &pipes, const Texture & pipe_texture) {
    best_score = std::max(score, best_score);
    score = 0;
    bird.die();

    pipes.clear();

    for (int i = 0; i < MAX_PIPES; i++) {
        auto p = Pipe {
            getRandomOpening(i),
            pipe_texture,
        };
        pipes.push_back(p);
    }
}

Rectangle getRandomOpening(size_t idx) {
    return Rectangle{
        START_OFFSET + idx * (float) PIPE_PADDING,
        (float) GetRandomValue(50, (SCREEN_HEIGHT - 80) - OPENING_HEIGHT),
        OPENING_WIDTH,
        OPENING_HEIGHT,
    };
}
