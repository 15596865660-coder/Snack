// 作者: 邓泽林  班级: 计科2501
#pragma once
#include <vector>

struct Point {
    int x;
    int y;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
private:
    std::vector<Point> body;
    Direction dir;

public:
    Snake();
    const std::vector<Point>& GetBody() const;
    Point GetHead() const;
    Direction GetDirection() const;
    void ChangeDirection(Direction newDir);
    void Move(bool eatFood);
    bool CheckCollision() const;
};