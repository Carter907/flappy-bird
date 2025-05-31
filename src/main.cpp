#include "bird.h"
#include "game.h"
#include <iostream>
#include <raylib.h>
#include <cstdio>
#include <vector>

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "flappybird!");
    SetWindowMaxSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(60);

    Font fnt = LoadFont("assets/UbuntuMono-B.ttf");
    Image birdImg = LoadImage("assets/flappybird.png");
    Image backgroundImg = LoadImage("assets/background.jpg");
    Image pipeImg = LoadImage("assets/pipe.png");

    Texture2D birdTexture = LoadTextureFromImage(birdImg);
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);
    Texture2D pipeTexture = LoadTextureFromImage(pipeImg);

    char scoreText[30];
    char bestScoreText[30];

    Game * game = new Game();
    Bird * bird = new Bird(birdTexture);

    std::vector<Rectangle> pipes;

    for (int i = 0; i < MAX_PIPES; i++) {
        pipes.push_back(getRandomOpening(i));
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawTextureEx(backgroundTexture, Vector2{0, -150}, 0, 0.8, WHITE);


        if (bird->update()) {
            game->restart(bird, pipes);
        }
        bird->draw();


        for (auto &pipe: pipes) {
            auto [x, y, width, height] = pipe;

            if (BIRD_START_X + birdTexture.width * 0.15 >= x && BIRD_START_X <= x + width) {
                if (bird->y_pos < y ||
                    bird->y_pos + birdTexture.height * 0.15 >
                    y + height) {
                    game->restart(bird, pipes);
                    continue;
                }
            }
            DrawTexturePro(
                pipeTexture,
                Rectangle{
                    0, 0, static_cast<float>(pipeTexture.width),
                    static_cast<float>(pipeTexture.height)
                },
                Rectangle{x, y + OPENING_HEIGHT, OPENING_WIDTH, 500},
                Vector2{0, 0}, 0, WHITE);

            DrawTexturePro(
                pipeTexture,
                Rectangle{
                    0, 0, static_cast<float>(pipeTexture.width),
                    static_cast<float>(pipeTexture.height)
                },
                Rectangle{x + OPENING_WIDTH, y, OPENING_WIDTH, 500},
                Vector2{0, 0}, 180, WHITE);

            pipe.x -= PIPE_SPEED * GetFrameTime();
        }


        if (pipes.front().x + OPENING_WIDTH < 0) {
            game->score++;

            pipes.erase(pipes.begin());
            const int prev_x = pipes.back().x;
            Rectangle ran_pipe_opening = {
                prev_x + static_cast<float>(PIPE_PADDING),
                static_cast<float>(GetRandomValue(50, (SCREEN_HEIGHT - 80) - OPENING_HEIGHT)),
                OPENING_WIDTH,
                OPENING_HEIGHT,
            };

            pipes.push_back(ran_pipe_opening);
        }

        sprintf(scoreText, "score: %d", game->score);
        sprintf(bestScoreText, "best: %d", game->best_score);

        DrawTextEx(fnt, scoreText, Vector2{0, 0}, 30, 0, GREEN);
        DrawTextEx(fnt, bestScoreText,
                   Vector2{static_cast<float>(MeasureText(scoreText, 30)), 0}, 30, 0, GREEN);

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
