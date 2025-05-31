#ifndef BIRD_H
#define BIRD_H

#include <raylib.h>
#define FLAP_VELOCITY 500
#define BIRD_START_X 50 // starting x position
#define BIRD_START_Y 100 // starting x position
#define FALL_RATE 2000 // pixels per second

struct Bird {

  float velocity = 0;
  float y_pos = BIRD_START_Y;
  Texture2D texture;
  bool update();
  void draw() const;
  void flap();
  void die();

  Bird(const Texture2D& texture) : texture(texture) {}
};

#endif
