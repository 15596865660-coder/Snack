// 作者: 邓泽林  班级: 计科2501
#include "pch.h"
#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food() {
    position = { 10, 10 };
    srand((unsigned int)time(NULL));
}


Point Food::GetPosition() const {
    return position;
}

void Food::GenerateFood(int mapWidth, int mapHeight, const std::vector<Point>& snakeBody) {

    while (true) {

        int randX = rand() % mapWidth;
        int randY = rand() % mapHeight;


        bool isOnSnake = false;
        for (const auto& block : snakeBody) {
            if (block.x == randX && block.y == randY) {
                isOnSnake = true;
                break;
            }
        }


        if (!isOnSnake) {

            position.x = randX;
            position.y = randY;
            break;
        }

    }
}