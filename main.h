#ifndef SNAKEGAME_MAIN_H
#define SNAKEGAME_MAIN_H
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <cstdio>
#include <termios.h>
#include <unistd.h>

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction Dir = STOP;
bool ateflag = false;
bool endflag = false;

void MapConvert (int &x, int &y, std::vector<std::vector<unsigned char>>& image) {
    std::ifstream f;
    if (endflag)
    {
        f.open("../cat.txt");
    }
    else
    {
        f.open("../map.txt");
    }
    if (!f.is_open()) {
        std::cerr << "Ошибка в открытии файла." << strerror(errno) << std::endl;
        return;
    }
    std::cout << "Карта открыта успешно.\n";
    std::string line;
    //int maxrows = 1000;
    //int maxcols = 1000;
    int j = 0;
    getline(f, line);
    int linecount=0;
    int linelength = static_cast<int>(line.size());
    for (int i = 0; i<linelength; i++) {
        if (line.at(i) == '\n')
        {linecount++;}
    }
    int xmax;
    while (std::getline(f, line)) {
        std::vector<unsigned char> row;
        x = 0;
        for (char &c : line) {
            if (c != '\n') {
                x++;
                row.push_back(c);
            }
        }
        if (x>xmax)
        {xmax = x;}
        y++;
        image.push_back(row);
    }
    /*for (int i = 0; i<linelength-linecount; i++) {
        if (line.at(i) == '\n') {
            i++;
            j++;
        }
        std::cout << "shit";
        unsigned char lineat = line.at(i);
        image.push_back({lineat});
        std::cout << "shit";
    }*/
    f.close();
    std::cout << "Карта конвертирована успешно.\n";
    x = xmax;
    if (y < 25 || x < 30) {
        std::cout << "Предупреждение: Карта меньше 30x25, возможна ошибка в программе.\n";
    }
}

void NextFrame(int &x, int &y, Direction D, int& len,
    int *TailX, int *TailY, int sc, std::vector<std::vector<unsigned char>>& image)
{
    int prevX = TailX[1];
    int prevY = TailY[1];
    TailX[1] = x;
    TailY[1] = y;
    for (int i = 1; i < len; i++)
    {
        int prev2X = TailX[i];
        int prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (D) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    // столк. с едой
    if (image[y][x] == 'O')
    {
        sc += 1;
        len++;
        image[y][x] = ' ';
        ateflag = true;
    }
}
bool GameOver(int x, int y, int len, int *TailX,
    int *TailY, int w, int h, std::vector<std::vector<unsigned char>> image)
{
    //столк. со стеной или границами карты
    if ((y >= h) || (x >= w) || (y < 0) ||
    (x < 0) || (image[y][x] == 'X'))
    {
        return true;
    }
    //столк. с хвостом
    for (int i = 1; i < len; i++)
    {
        if (TailX[i] == x && TailY[i] == y)
        {
            return true;
        }
    }
    //существует еда
    /*if (ateflag == true)
    {
        ateflag = false;
        for (int i = 0; i<h; i++)
        {
            for (int j = 0; j<w; j++)
            {
                if( image[i][j] == 'O')
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {*/
        return false;
    //}
}

void GameRender(std::vector<std::vector<unsigned char>> image, int sc, int x,
    int y, int len, int *tailx, int *taily)
{
    system("clear");
    for (int i = 0; i < 30 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j <= 30; j++)
        {
            if (j == 0 || j == 30)
            {
                std::cout << "|";
            }
            if (i == y && j == x)
            {
                std::cout << "U";
            }
            else
            {

                bool prTail = false;
                for (int k = 0; k < len; k++) {
                    if (tailx[k] == j
                        && taily[k] == i)
                    {
                        std::cout << "#";
                        prTail = true;
                    }
                }
                if (!prTail)
                {
                    std::cout << image[i][j];
                }

            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 30 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "Счёт: " << sc << std::endl;
}
void EndState(int sc, int w, int h, std::vector<std::vector<unsigned char>>& image)
{
    system("clear");
    endflag;
    image.clear();
    for (int i = 0; i < 25 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout <<"\n";
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j <= 30; j++) 
        {
            std::cout << "💥"; 
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 30 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "Счёт: " << sc << std::endl;
    int x = 1;
    //MapConvert(w, h, image);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("clear");
    /*for (int i = 0; i < 25 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j <= 30; j++) 
        {
            if (j == 0 || j == 30)
            {
                std::cout << "|";
            }
            std::cout << image[i][j];
            }
        std::cout << std::endl;
    }
    for (int i = 0; i < 30 + 2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "Счёт: " << sc << std::endl;*/
}
void Userinput()
{
    struct termios oldSettings, newSettings;

    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );

    while ( 1 )
    {
        fd_set set;
        struct timeval tv;

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 )
        {
            char c;
            read( fileno( stdin ), &c, 1 );
            switch(c)
            {
                case 'w':
                    Dir = UP;
                    break;
                case 'a':
                    Dir = LEFT;
                    break;
                case 's':
                    Dir = DOWN;
                    break;
                case 'd':
                    Dir = RIGHT;
                    break;
                case 'W':
                    Dir = UP;
                    break;
                case 'A':
                    Dir = LEFT;
                    break;
                case 'S':
                    Dir = DOWN;
                    break;
                case 'D':
                    Dir = RIGHT;
                    break;
                default:
                    std::cout << "Possible user deviation";
                    break;
            }
        }
        else if( res < 0 )
        {
            perror( "select error" );
            break;
        }
        else
        {
            printf( "Select timeout\n" );
        }
    }
    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
}
#endif // SNAKEGAME_MAIN_H