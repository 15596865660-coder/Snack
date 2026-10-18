// 作者: 邓泽林  班级: 计科2501
#pragma once

#include "Snake.h"
#include <vector>

class Food {
private:
    Point position;

public:
    Food();

    Point GetPosition() const;

    void GenerateFood(int mapWidth, int mapHeight, const std::vector<Point>& snakeBody);
};
