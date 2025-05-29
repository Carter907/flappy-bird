#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <vector>

int main(int argc, char **argv) {

  const int screenWidth = 800;
  const int screenHeight = 450;
  const bool debug = false;
  const float gravity = 9.81; // measured in meters per second

  InitWindow(screenWidth, screenHeight, "flappybird!");

  Font fnt = LoadFont("assets/UbuntuMono-B.ttf");
  Image birdImg = LoadImage("assets/flappybird.png");
  Image backgroundImg = LoadImage("assets/background.jpg");
  Image pipeImg = LoadImage("assets/pipe.png");

  Texture2D birdTexture = LoadTextureFromImage(birdImg);
  Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);
  Texture2D pipeTexture = LoadTextureFromImage(pipeImg);

  SetTargetFPS(60);

  int score = 0;
  int best_score = 0;
  bool restart = false;
  char scoreText[30];
  char bestScoreText[30];
  char birdVeloYText[30];
  char birdYText[30];
  int birdY = 50, birdVeloY = 0; // measured in pixels per second

  const int max_pipes = 5;
  const int pipe_speed = 300; // pixels per second
  const int pipe_pad = 500;
  const int bird_start = 50;
  const int start_offset = 1000;
  const int opening_width = 100;
  const int opening_height = 150;
  std::vector<Rectangle> pipes;

  for (int i = 0; i < max_pipes; i++) {
    Rectangle ran_pipe_opening = {
        start_offset + i * (float)pipe_pad,
        (float)GetRandomValue(50, (screenHeight - 80) - opening_height),
        opening_width,
        opening_height,
    };

    pipes.push_back(ran_pipe_opening);
  }

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(SKYBLUE);

    if (restart) {

      best_score = std::max(score, best_score);
      score = 0;
      birdY = 50;
      birdVeloY = 0;

      pipes.clear();

      for (int i = 0; i < max_pipes; i++) {
        Rectangle ran_pipe_opening = {
            start_offset + i * (float)pipe_pad,
            (float)GetRandomValue(50, (screenHeight - 80) - opening_height),
            opening_width,
            opening_height,
        };

        pipes.push_back(ran_pipe_opening);
      }

      restart = false;
    }

    birdVeloY -= gravity * 100 * GetFrameTime();
    int chVeloY = birdVeloY * GetFrameTime();

    if (birdY - chVeloY < 0) {
      restart = true;
      continue;
    } else if (birdY - chVeloY > GetScreenHeight() - 80) {
      restart = true;
      continue;
    }
    birdY -= chVeloY;

    if (IsKeyPressed(KEY_SPACE)) {
      if (birdVeloY < 40) {
        birdVeloY = gravity * 50;
      }
    }

    DrawTextureEx(backgroundTexture, Vector2{0, -150}, 0, 0.8, WHITE);
    DrawTextureEx(birdTexture, Vector2{bird_start, (float)birdY}, 0, 0.15,
                  WHITE);

    for (int i = 0; i < pipes.size(); i++) {
      Rectangle rect = pipes[i];

      if (bird_start >= rect.x && bird_start < rect.x + rect.width) {

        if (birdY < rect.y ||
            birdY + birdTexture.height * 0.15 > rect.y + rect.height) {
          restart = true;
          continue;
        }
      }

      DrawTexturePro(
          pipeTexture,
          Rectangle{0, 0, (float)pipeTexture.width, (float)pipeTexture.height},
          Rectangle{rect.x, rect.y + opening_height, opening_width, 500},
          Vector2{0, 0}, 0, WHITE);
      DrawTexturePro(
          pipeTexture,
          Rectangle{0, 0, (float)pipeTexture.width, (float)pipeTexture.height},
          Rectangle{rect.x + opening_width, rect.y, opening_width, 500},
          Vector2{0, 0}, 180, WHITE);

      pipes[i].x -= pipe_speed * GetFrameTime();
    }

    if (pipes.front().x + opening_width < 0) {
      for (auto &pipe : pipes) {
        std::cout << pipe.x << ", " << pipe.y << ", " << pipe.width << ", "
                  << pipe.height << std::endl;
      }
      score++;

      pipes.erase(pipes.begin());
      int prev_x = pipes.back().x;
      Rectangle ran_pipe_opening = {
          prev_x + (float)pipe_pad,
          (float)GetRandomValue(50, (screenHeight - 80) - opening_height),
          opening_width,
          opening_height,
      };

      pipes.push_back(ran_pipe_opening);
    }

    sprintf(scoreText, "score: %d", score);
    sprintf(bestScoreText, "best: %d", best_score);

    DrawTextEx(fnt, scoreText, Vector2{0, 0}, 30, 0, GREEN);
    DrawTextEx(fnt, bestScoreText,
               Vector2{(float)MeasureText(scoreText, 30), 0}, 30, 0, GREEN);

    if (debug) {
      sprintf(birdYText, "y: %d", birdY);
      sprintf(birdVeloYText, "velocity: %d", birdVeloY);

      DrawTextEx(fnt, birdYText,
                 Vector2{(float)MeasureText(bestScoreText, 30), 0}, 20, 0, RED);

      DrawTextEx(fnt, birdVeloYText,
                 Vector2{(float)MeasureText(birdYText, 20), 0}, 20, 0, RED);
    }

    EndDrawing();
  }

  UnloadFont(fnt);
  CloseWindow();
  return 0;
}
