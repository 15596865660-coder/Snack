#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GameManager.h"

void ShowInstructions();

int main() {
    SetConsoleTitleA("Snake Game v1.0");

    int selectedOption = 0;

    while (true) {
        system("cls");
        std::cout << "============================================\n";
        std::cout << "           S N A K E   G A M E              \n";
        std::cout << "============================================\n\n";

        if (selectedOption == 0) {
            std::cout << "       >  1. Start Game  <\n";
        }
        else {
            std::cout << "          1. Start Game\n";
        }

        if (selectedOption == 1) {
            std::cout << "       >  2. Instructions  <\n";
        }
        else {
            std::cout << "          2. Instructions\n";
        }

        if (selectedOption == 2) {
            std::cout << "       >  3. Exit  <\n";
        }
        else {
            std::cout << "          3. Exit\n";
        }

        std::cout << "\n============================================\n";
        std::cout << " Use [Up/Down] to select, [Enter] to confirm\n";
        std::cout << "============================================\n";

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == 72) {
                selectedOption--;
                if (selectedOption < 0) selectedOption = 2;
            }
            else if (ch == 80) {
                selectedOption++;
                if (selectedOption > 2) selectedOption = 0;
            }
        }
        else if (ch == 13) {
            if (selectedOption == 0) {
                GameManager game;
                game.Run();

                std::cout << "\n[Press any key to return to menu]..." << std::endl;
                _getch();
            }
            else if (selectedOption == 1) {
                ShowInstructions();
            }
            else if (selectedOption == 2) {
                system("cls");
                std::cout << "\nThanks for playing!\n\n";
                Sleep(1000);
                break;
            }
        }
    }

    return 0;
}

void ShowInstructions() {
    system("cls");
    std::cout << "============================================\n";
    std::cout << "             Instructions                   \n";
    std::cout << "============================================\n\n";
    std::cout << "  1. Controls:\n";
    std::cout << "     Use arrow keys [Up/Down/Left/Right]\n";
    std::cout << "     to control the snake.\n\n";
    std::cout << "  2. Rules:\n";
    std::cout << "     - Eat food to grow longer and score.\n";
    std::cout << "     - Don't hit walls or yourself.\n\n";
    std::cout << "  3. Tips:\n";
    std::cout << "     Please switch to English input mode!\n\n";
    std::cout << "============================================\n";
    std::cout << "[Press any key to return to menu]...";

    _getch();
}