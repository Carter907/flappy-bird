#include "raylib.h"
#include <stdio.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  const bool debug = true;
  const float gravity = 9.81; // measured in meters per second

  InitWindow(screenWidth, screenHeight, "flappybird!");

  Font fnt = LoadFont("assets/UbuntuMono-B.ttf");
  Image birdImg = LoadImage("assets/flappybird.png");
  Image backgroundImg = LoadImage("assets/background.jpg");

  Texture2D birdTexture = LoadTextureFromImage(birdImg);
  Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

  SetTargetFPS(60);

  int score = 0;
  char scoreText[30];
  char birdVeloYText[30];
  char birdYText[30];
  int birdY = 50, birdVeloY = 0; // measured in pixels per second

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(SKYBLUE);

    birdVeloY -= gravity * 100 * GetFrameTime();
    birdY -= birdVeloY * GetFrameTime();

    if (IsKeyPressed(KEY_SPACE)) {
      if (birdVeloY < 50) {

        birdVeloY += gravity * 75;
      }
    }

    if (birdY > screenHeight) {
      birdY = screenHeight;
    }

    DrawTextureEx(backgroundTexture, Vector2{0, -150}, 0, 0.8, WHITE);
    DrawTextureEx(birdTexture, Vector2{50, (float)birdY}, 0, 0.15, WHITE);
    sprintf(scoreText, "score: %d", score);
    DrawTextEx(fnt, scoreText, Vector2{0, 0}, 20, 5, LIGHTGRAY);

    if (debug) {
      sprintf(birdYText, "y: %d", birdY);
      sprintf(birdVeloYText, "velocity: %d", birdVeloY);

      DrawTextEx(fnt, birdYText,
                 Vector2{(float)MeasureText(scoreText, 20) + 50, 0}, 20, 5,
                 LIGHTGRAY);

      DrawTextEx(fnt, birdVeloYText,
                 Vector2{(float)MeasureText(birdYText, 20) + 200, 0}, 20, 5,
                 LIGHTGRAY);
    }

    EndDrawing();
  }

  UnloadFont(fnt);
  CloseWindow();
  return 0;
}
