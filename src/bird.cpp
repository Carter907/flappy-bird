#include "bird.h"

void Bird::update(bool & restart) {
  set_velocity(get_velocity() - FALL_RATE * GetFrameTime());
  int delta_v = get_velocity() * GetFrameTime();

  if (get_y_pos() - delta_v < 0) {
    restart = true;
  }
  if (get_y_pos() - delta_v > GetScreenHeight() - 80) {
    restart = true;
  }

  set_y_pos(get_y_pos() - delta_v);
  if (IsKeyPressed(KEY_SPACE)) {
    if (velocity < 40) {
      velocity = FLAP_VELOCITY;
    }
  }
}

void Bird::draw() const {

  DrawTextureEx(texture, Vector2{BIRD_START_X, static_cast<float>(y_pos)}, 0, 0.15, WHITE);
}

void Bird::flap() { velocity = FLAP_VELOCITY; }

void Bird::die() {
  velocity = 0;
  y_pos = 50;
}

void Bird::set_velocity(int velocity) { this->velocity = velocity; }
void Bird::set_y_pos(int y_pos) { this->y_pos = y_pos; }
int Bird::get_velocity() const { return velocity; }
int Bird::get_y_pos() const { return y_pos; }
