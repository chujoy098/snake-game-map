#include <iostream>
#include <chrono>
#include <thread>
#include "../include/main.h"
#include <vector>
#include <bits/stdc++.h>

int main()
{
    std::cout << "ЗМЕЙКА.\n";
    int choice, x=0, y=0;
    std::cout << "Начать игру - 1, выход - 2\n";
    do
    {
    std::cin >> choice;
    } while (choice != 1 && choice != 2);
    if(choice == 1) {
        std::cout << "ok.\n";
        int height, width;
        std::vector<std::vector<unsigned char>> im;
    MapConvert(width, height, im);
        x = 5, y = 5;
    int snakeTailX[100], snakeTailY[100],
        playerScore = 0, TailLen = 0;
    bool GOflag = false;
    std::thread inp(Userinput);
    do
    {
        GOflag = GameOver(x, y, TailLen, snakeTailX,
            snakeTailY, width, height, im);
        if (GOflag == true)
        {
            EndState(playerScore, width, height, im);
        }
        else
        {
            GameRender(im, playerScore, x, y, TailLen,
            snakeTailX, snakeTailY);
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            NextFrame(x, y, Dir, TailLen, snakeTailX,
            snakeTailY, playerScore, im);
        }
        } while(GOflag == false);
        }
    else
        {
        return 0;
        }
    return 0;
}