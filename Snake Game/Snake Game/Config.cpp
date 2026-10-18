#include "pch.h"
#include "Config.h"
#include <iostream>

using std::cout;
using std::endl;

Config::Config() {
    width = 50;
    height = 40;
    gameSpeed = 150;
    scoreReward = 10;
}

int Config::GetWidth()       const { return width; }
int Config::GetHeight()      const { return height; }
int Config::GetSpeed()       const { return gameSpeed; }
int Config::GetScoreReward() const { return scoreReward; }

bool Config::IsPointInside(Point p) const {
    if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height) {
        return true;
    }
    return false;
}

void Config::Draw(const std::vector<Point>& snakeBody, Point foodPos, int score, bool isGameOver) const {
    system("cls");

    for (int y = -1; y <= height; y++) {
        for (int x = -1; x <= width; x++) {

            if (x == -1 || x == width || y == -1 || y == height) {
                cout << "#";
            }
            else if (x == snakeBody.front().x && y == snakeBody.front().y) {
                cout << "@";
            }
            else {
                bool isBody = false;
                for (size_t i = 1; i < snakeBody.size(); ++i) {
                    if (x == snakeBody[i].x && y == snakeBody[i].y) {
                        isBody = true;
                        break;
                    }
                }

                if (isBody) {
                    cout << "o";
                }
                else if (x == foodPos.x && y == foodPos.y) {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << "-------------------------" << endl;
    cout << "Score: " << score << endl;
    cout << "Use arrow keys to move" << endl;
    cout << "-------------------------" << endl;

    if (isGameOver) {
        cout << "  GAME OVER!  " << endl;
        cout << "-------------------------" << endl;
    }
}