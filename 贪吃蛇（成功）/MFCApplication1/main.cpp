// 作者: 邓泽林  班级: 计科2501
#include <iostream>
#include <conio.h>     // 用于 _kbhit() 和 _getch()
#include <windows.h>   // 用于 system("cls") 和 Sleep()
#include "GameManager.h"

// 函数声明：显示游戏说明界面
void ShowInstructions();

int main() {
    // 设置控制台窗口标题
    SetConsoleTitleA("贪吃蛇大作战 v1.0");

    int selectedOption = 0; // 当前光标选中的菜单项（0:开始游戏, 1:游戏说明, 2:退出游戏）

    // 主菜单无限循环
    while (true) {
        // 1. 清屏并绘制菜单界面
        system("cls");
        std::cout << "============================================\n";
        std::cout << "         ★ 贪 吃 蛇 大 作 战 ★            \n";
        std::cout << "============================================\n\n";

        // 动态绘制选项，选中的那一行的前面会带上一个小箭头 "?"
        if (selectedOption == 0) {
            std::cout << "       ?  1. 开始游戏  ?\n";
        }
        else {
            std::cout << "          1. 开始游戏\n";
        }

        if (selectedOption == 1) {
            std::cout << "       ?  2. 游戏说明  ?\n";
        }
        else {
            std::cout << "          2. 游戏说明\n";
        }

        if (selectedOption == 2) {
            std::cout << "       ?  3. 退出游戏  ?\n";
        }
        else {
            std::cout << "          3. 退出游戏\n";
        }

        std::cout << "\n============================================\n";
        std::cout << " 提示: 请使用键盘右下角 [ ↑ ↓ ] 键移动光标\n";
        std::cout << "       按下 [ Enter 回车键 ] 确认选择\n";
        std::cout << "       游玩前请确保输入法为【英文】状态\n";
        std::cout << "============================================\n";

        // 2. 捕捉菜单界面的按键输入
        int ch = _getch();

        // 处理方向键（双字节键）
        if (ch == 0 || ch == 224) {
            ch = _getch(); // 获取具体方向码
            if (ch == 72) { // 键盘 【↑】 键
                selectedOption--;
                if (selectedOption < 0) selectedOption = 2; // 循环滚动：到最顶上后去最底下的选项
            }
            else if (ch == 80) { // 键盘 【↓】 键
                selectedOption++;
                if (selectedOption > 2) selectedOption = 0; // 循环滚动：到最底下后去最顶上的选项
            }
        }
        // 处理 【Enter 回车键】（ASCII 码为 13）
        else if (ch == 13) {
            if (selectedOption == 0) {
                // 【选项 0：开始游戏】
                // 每次在这里新建 GameManager，天然保证了所有游戏数据、分数、坐标都是全新的！
                GameManager game;
                game.Run(); // 进入游戏主循环，直到 Game Over 才会退出这个函数

                // 游戏结束后，在原地卡住，给玩家一个心理缓冲，按任意键再退回主菜单
                std::cout << "\n【按下任意键返回主菜单】..." << std::endl;
                _getch();
            }
            else if (selectedOption == 1) {
                // 【选项 1：游戏说明】
                ShowInstructions();
            }
            else if (selectedOption == 2) {
                // 【选项 2：退出游戏】
                system("cls");
                std::cout << "\n感谢游玩，再见！\n\n";
                Sleep(1000); // 延迟 1 秒后退出
                break;       // 跳出大循环，程序正常结束
            }
        }
    }

    return 0;
}

// 绘制“游戏说明”子界面
void ShowInstructions() {
    system("cls");
    std::cout << "============================================\n";
    std::cout << "               栏目：游戏说明               \n";
    std::cout << "============================================\n\n";
    std::cout << "  1. 操控方式：\n";
    std::cout << "     游戏开始后，使用键盘右下角的 [ ↑ ↓ ← → ]\n";
    std::cout << "     独立方向键来控制小蛇的上下左右移动。\n\n";
    std::cout << "  2. 核心规则：\n";
    std::cout << "     - 操控小蛇去吃掉屏幕中随机出现的食物。\n";
    std::cout << "     - 每吃掉一个食物，身体会变长，得分也会增加。\n";
    std::cout << "     - 绝对不能撞到墙壁，也不能咬到自己的身体。\n\n";
    std::cout << "  3. 避坑指南：\n";
    std::cout << "     如果按键没反应，请确认关闭了电脑的中文输入法！\n\n";
    std::cout << "============================================\n";
    std::cout << "【按下任意键返回主菜单】...";

    _getch(); // 等待玩家按下任意键，随后函数结束，自动回到 main 的主循环
}