#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <cmath>

// #include "astar.cpp"

using namespace std;

void gen();

enum Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

bool over;

int w,
    h;
int px, py;
int x, y;
int score;
int len;
int tx[100], ty[100];
Direction dir;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CHAR_INFO chibuf[2000];
SMALL_RECT sr;
COORD c, c1;

void setup()
{
    c.X = 0, c.Y = 0;
    c1.X = 80, c1.Y = 25;

    sr.Top = 0;
    sr.Bottom = 24;
    sr.Left = 0;
    sr.Right = 79;

    over = false;
    w = 80 - 2, h = 25 - 2;
    x = 0, y = 0;
    gen();
    score = 0;
    len = 0;
    dir = (Direction)(rand() % 4);
}
void draw()
{
    for (int j = -1; j <= h; j++)
    {
        for (int i = -1; i <= w; i++)
        {
            int bufCoord = (j + 1) * (w + 2) + (i + 1);
            if (j == -1 || j == h || i == w || i == -1)
            {
                chibuf[bufCoord].Char.AsciiChar = '#';
                chibuf[bufCoord].Attributes = 25;
            }
            else if (x == i && y == j)
            {
                chibuf[bufCoord].Char.AsciiChar = 'O';
                chibuf[bufCoord].Attributes = 45;
            }
            else
            {
                bool printed = false;

                for (int k = 0; k < len; k++)
                    if (tx[k] == i && ty[k] == j)
                    {
                        printed = true;
                        chibuf[bufCoord].Char.AsciiChar = 'o';
                        chibuf[bufCoord].Attributes = 50;
                    }
                if (!printed)
                {
                    if (px == i && py == j)
                    {
                        chibuf[bufCoord].Char.AsciiChar = '*';
                        chibuf[bufCoord].Attributes = 99;
                    }
                    else
                    {
                        chibuf[bufCoord].Char.AsciiChar = ' ';
                        chibuf[bufCoord].Attributes = 75;
                    }
                }
            }
        }
    }

    WriteConsoleOutputA(handle, chibuf, c1, c, &sr);
}
void input()
{
    if (!_kbhit())
        return;

    Direction _dir;

    switch (_getch())
    {
    case 'a':
        _dir = LEFT;
        break;
    case 'w':
        _dir = UP;
        break;
    case 'd':
        _dir = RIGHT;
        break;
    case 's':
        _dir = DOWN;
        break;
    }

    if (abs((int)dir - (int)_dir) != 2) {
        dir = _dir;
        
    }
}
void logic()
{
    int _x = tx[0], _y = ty[0];
    int _x2, _y2;
    tx[0] = x, ty[0] = y;
    for (int k = 1; k < len; k++)
    {
        _x2 = tx[k], _y2 = ty[k];
        tx[k] = _x, ty[k] = _y;
        _x = _x2, _y = _y2;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case RIGHT:
        x++;
        break;
    case LEFT:
        x--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x == -1)
        x = w - 1;
    else if (x == w)
        x = 0;

    if (y == -1)
        y = h - 1;
    else if (y == h)
        y = 0;

    for (int k = 0; k < len; k++)
    {
        if (tx[k] == x && ty[k] == y)
        {
            over = true;
        }
    }

    if (px == x && py == y)
    {
        score += 1;
        len += 1;
        gen();
    }
}

void gen()
{
    px = rand() % w;
    py = rand() % h;
}

int main()
{
    setup();
    while (!over)
    {
        draw();
        input();
        logic();
        Sleep(100 / pow(score + 1, 1 / 3));
    }
}