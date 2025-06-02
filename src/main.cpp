#include "bird.h"
#include "game.h"
#include "pipe.h"
#include <iostream>
#include <raylib.h>
#include <cstdio>
#include <vector>
#include <deque>

#define SCORE_TEXT_LENGTH 30
#define BEST_SCORE_TEXT_LENGTH 30


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "flappybird!");
    SetWindowMaxSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(60);

    const Font fnt = LoadFont("assets/UbuntuMono-B.ttf");
    const Image birdImg = LoadImage("assets/flappybird.png");
    const Image backgroundImg = LoadImage("assets/background.jpg");
    const Image pipeImg = LoadImage("assets/pipe.png");

    const Texture2D birdTexture = LoadTextureFromImage(birdImg);
    const Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);
    const Texture2D pipeTexture = LoadTextureFromImage(pipeImg);

    char scoreText[SCORE_TEXT_LENGTH];
    char bestScoreText[BEST_SCORE_TEXT_LENGTH];

    auto game = Game();
    auto bird = Bird(birdTexture);

    std::deque<Pipe> pipes;

    for (int i = 0; i < MAX_PIPES; i++) {
        auto p = Pipe {
            getRandomOpening(i),
            pipeTexture,
        };
        pipes.push_back(p);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawTextureEx(backgroundTexture, Vector2{0, -150}, 0, 0.8, WHITE); // draw background

        snprintf(scoreText, SCORE_TEXT_LENGTH, "score: %d", game.score);
        snprintf(bestScoreText, BEST_SCORE_TEXT_LENGTH, "best: %d", game.best_score);

        DrawTextEx(fnt, scoreText, Vector2{0, 0}, 30, 0, GREEN);
        DrawTextEx(fnt, bestScoreText,
                   Vector2{static_cast<float>(MeasureText(scoreText, 30)), 0}, 30, 0, GREEN);

        if (bird.update()) {
            game.restart(bird, pipes, pipeTexture);
        }
        bird.draw();

        for (auto &pipe: pipes) {

            if (birdHitPipe(pipe, bird)) {
                game.restart(bird, pipes, pipeTexture);
                continue;
            }

            pipe.opening_bounds.x -= PIPE_SPEED * GetFrameTime();

            pipe.draw();
        }


        if (pipes.front().opening_bounds.x + OPENING_WIDTH < 0) {

            game.score++;
            pipes.erase(pipes.begin());

            auto new_pipe = Pipe {
                getRandomOpening(pipes.size()-1),
                pipeTexture,
            };
            pipes.push_back(new_pipe);
        }

        EndDrawing();
    }

    UnloadFont(fnt);

    UnloadTexture(birdTexture);
    UnloadImage(birdImg);

    UnloadTexture(pipeTexture);
    UnloadImage(pipeImg);

    UnloadTexture(backgroundTexture);
    UnloadImage(backgroundImg);

    CloseWindow();
    return 0;
}


