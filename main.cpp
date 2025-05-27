#include "raylib.h"
#include <stdio.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  int score = 0;
  char scoreText[20];

  InitWindow(screenWidth, screenHeight, "flappybird!");

  Font fnt = LoadFont("assets/UbuntuMono-B.ttf");
  Image birdImg = LoadImage("assets/flappybird.png");
  Image backgroundImg = LoadImage("assets/background.jpg");

  Texture2D birdTexture = LoadTextureFromImage(birdImg);
  Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(SKYBLUE);
    sprintf(scoreText, "score: %d", score);
    DrawTextEx(fnt, scoreText, Vector2{0, 0}, 30, 5, LIGHTGRAY);

    // Rectangle birdSrc =
    //     Rectangle{(float)birdTexture.width, (float)birdTexture.height};
    // Rectangle birdDest = Rectangle{20, 20};
    // Rectangle bgSrc = Rectangle{(float)backgroundTexture.width,
    //                             (float)backgroundTexture.height};
    // Rectangle bgDest = Rectangle{screenWidth, screenHeight};
    //
    DrawTextureEx(backgroundTexture, Vector2{0, -150}, 0, 0.8,
                  WHITE); // Draw a Texture2D with extended parameters
    DrawTextureEx(birdTexture, Vector2{50, 50}, 0, 0.15,
                  WHITE); // Draw a Texture2D with extended parameters

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
