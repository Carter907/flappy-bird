#ifndef BIRD_H
#define BIRD_H

#include <raylib.h>
#define FLAP_VELOCITY 500
#define BIRD_START_X 50 // starting x position
#define BIRD_START_Y 100 // starting x position
#define FALL_RATE 2000 // pixels per second

class Bird {

  int velocity = 0;
  int y_pos = BIRD_START_Y;
  Texture2D texture;

public:
  void update(bool &restart);
  void draw() const;
  void flap();
  void die();
  void set_velocity(int velocity);
  void set_y_pos(int y_pos);
  int get_velocity() const;
  int get_y_pos() const;

  Bird(const Texture2D& texture) : texture(texture) {}
};

#endif
