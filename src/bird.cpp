#include "bird.h"

bool Bird::update() {
  velocity = velocity - FALL_RATE * GetFrameTime();
  const float delta_v = velocity * GetFrameTime();

  if (y_pos - delta_v < 0) {
    return true;
  }
  if (y_pos - delta_v > static_cast<float>(GetScreenHeight()) - 80) {
    return true;
  }

  y_pos = y_pos - delta_v;
  if (IsKeyPressed(KEY_SPACE)) {
    if (velocity < 40) {
      flap();
    }
  }
  return false;
}

void Bird::draw() const {

  DrawTextureEx(texture, Vector2{BIRD_START_X, static_cast<float>(y_pos)}, 0, 0.15, WHITE);
}

void Bird::flap() { velocity = FLAP_VELOCITY; }

void Bird::die() {
  velocity = 0;
  y_pos = 50;
}

