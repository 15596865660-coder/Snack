// 作者: 邓泽林  班级: 计科2501
#include "Snake.h"

Snake::Snake() {
    dir = RIGHT;
    body.push_back({ 5, 5 });
    body.push_back({ 4, 5 });
    body.push_back({ 3, 5 });
}

const std::vector<Point>& Snake::GetBody() const { return body; }

Point Snake::GetHead() const { return body.front(); }

Direction Snake::GetDirection() const { return dir; }

void Snake::ChangeDirection(Direction newDir) {
    if (newDir == UP && dir != DOWN) dir = newDir;
    if (newDir == DOWN && dir != UP) dir = newDir;
    if (newDir == LEFT && dir != RIGHT) dir = newDir;
    if (newDir == RIGHT && dir != LEFT) dir = newDir;
}

void Snake::Move(bool eatFood) {
    Point nextHead = GetHead();

    switch (dir) {
    case UP:    nextHead.y--; break;
    case DOWN:  nextHead.y++; break;
    case LEFT:  nextHead.x--; break;
    case RIGHT: nextHead.x++; break;
    }

    body.insert(body.begin(), nextHead);

    if (!eatFood) {
        body.pop_back();
    }
}

bool Snake::CheckCollision() const {
    Point head = body.front();

    for (size_t i = 1; i < body.size(); ++i) {
        if (head.x == body[i].x && head.y == body[i].y) {
            return true;
        }
    }
    return false;
}