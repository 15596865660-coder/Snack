#include "pch.h"
#include "GameManager.h"
#include <conio.h>
#include <windows.h>

GameManager::GameManager() {
    score = 0;
    isGameOver = false;
    food.GenerateFood(gameConfig.GetWidth(), gameConfig.GetHeight(), snake.GetBody());
}

void GameManager::Input() {
    if (_kbhit()) {

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();

            switch (ch) {
            case 72: snake.ChangeDirection(UP);    break;
            case 80: snake.ChangeDirection(DOWN);  break;
            case 75: snake.ChangeDirection(LEFT);  break;
            case 77: snake.ChangeDirection(RIGHT); break;
            }
        }
    }
}

void GameManager::Update() {
    if (isGameOver) return;

    Point nextHead = snake.GetHead();

    switch (snake.GetDirection()) {
    case UP:    nextHead.y--; break;
    case DOWN:  nextHead.y++; break;
    case LEFT:  nextHead.x--; break;
    case RIGHT: nextHead.x++; break;
    }

    bool eatFood = (nextHead.x == food.GetPosition().x && nextHead.y == food.GetPosition().y);

    snake.Move(eatFood);

    if (eatFood) {
        score += gameConfig.GetScoreReward();
        food.GenerateFood(gameConfig.GetWidth(), gameConfig.GetHeight(), snake.GetBody());
    }

    if (!gameConfig.IsPointInside(snake.GetHead()) || snake.CheckCollision()) {
        isGameOver = true;
    }
}

void GameManager::Run() {
    while (!isGameOver) {
        gameConfig.Draw(snake.GetBody(), food.GetPosition(), score, isGameOver);
        Input();
        Update();
        Sleep(gameConfig.GetSpeed());
    }
    gameConfig.Draw(snake.GetBody(), food.GetPosition(), score, isGameOver);
}