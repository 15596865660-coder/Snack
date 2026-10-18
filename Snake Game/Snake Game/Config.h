#pragma once

#include "Snake.h"
#include <vector>

class Config {
private:
    int width;
    int height;
    int gameSpeed;
    int scoreReward;

public:

    Config();


    int GetWidth() const;
    int GetHeight() const;
    int GetSpeed() const;
    int GetScoreReward() const;


    bool IsPointInside(Point p) const;


    void Draw(const std::vector<Point>& snakeBody, Point foodPos, int score, bool isGameOver) const;
};