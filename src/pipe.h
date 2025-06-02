#ifndef PIPE_H
#define PIPE_H

// amount of pipes in pipes vector
#define MAX_PIPES 5
// pipe speed measured in pixels per second
#define PIPE_SPEED 300
#include <raylib.h>

#include "bird.h"


struct Pipe {

    Rectangle opening_bounds;
    Texture2D texture;

    void draw() const;
    Pipe(const Rectangle bounds, const Texture2D &texture) : opening_bounds(bounds), texture(texture) {}
};


bool birdHitPipe(const Pipe& pipe, const Bird& bird);


#endif
