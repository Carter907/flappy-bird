#include "pipe.h"

#include <raylib.h>

#include "game.h"

void Pipe::draw() const {
    DrawTexturePro(
        texture,
        Rectangle{
            0, 0, static_cast<float>(texture.width),
            static_cast<float>(texture.height)
        },
        Rectangle{opening_bounds.x, opening_bounds.y + OPENING_HEIGHT, OPENING_WIDTH, 500},
        Vector2{0, 0}, 0, WHITE);

    DrawTexturePro(
        texture,
        Rectangle{
            0, 0, static_cast<float>(texture.width),
            static_cast<float>(texture.height)
        },
        Rectangle{opening_bounds.x + OPENING_WIDTH, opening_bounds.y, OPENING_WIDTH, 500},
        Vector2{0, 0}, 180, WHITE);
}

bool birdHitPipe(const Pipe& pipe, const Bird& bird) {

    return (BIRD_START_X + bird.texture.width * 0.15 >= pipe.opening_bounds.x
            && BIRD_START_X <= pipe.opening_bounds.x + pipe.opening_bounds.width) && (
               bird.y_pos < pipe.opening_bounds.y
               || bird.y_pos + bird.texture.height * 0.15 > pipe.opening_bounds.y + pipe.
               opening_bounds.height);
}
