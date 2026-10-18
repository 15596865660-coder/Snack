#pragma once
#include "Snake.h"
#include "Food.h"
#include "Config.h"

class GameManager {
private:
    Snake snake;
    Food food;
    Config gameConfig;
    int score;
    bool isGameOver;

    void Input();
    void Update();

public:
    GameManager();
    void Run();
};