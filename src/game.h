#ifndef GAME_H
#define GAME_H

#include <deque>
#include <raylib.h>
#include <deque>

#include "bird.h"
#include "pipe.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

// the width of the pipe openings
#define OPENING_WIDTH 100

// the height of the pipe openings
#define OPENING_HEIGHT 150

// the starting x offscreen that the pipes spawn
#define START_OFFSET 1000

// the pixel width between each pipe
#define PIPE_PADDING 500

struct Game {
    int score = 0;
    int best_score = 0;
    void restart(Bird& bird, std::deque<Pipe> &pipes, const Texture &pipe_texture);
};

// precondition: The index of the pipe on initialization of pipes vector
// postcondition: A rectangle signifying the opening of each pair of pipes
Rectangle getRandomOpening(size_t idx);


#endif
