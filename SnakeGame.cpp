#include "SnakeGame.h"

using namespace std;

void SnakeGame::Render() const
{
	system("cls");

    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            bool printed = false;

            for (const auto& segment : snake.GetBody()) 
            {
                if (segment.first == x && segment.second == y) 
                {
                    cout << "\033[44m" << "  " << "\033[0m";
                    printed = true;
                    break;
                }
            }

            if (!printed && apple.GetX() == x && apple.GetY() == y) 
            {
                cout << "\033[42m  \033[0m";
                printed = true;
            }

            if (!printed && dangerZone.GetX() == x && dangerZone.GetY() == y) 
            {
                cout << "\033[41m  \033[0m";
                printed = true;
            }

            if (!printed) 
            {
                cout << "\033[40m" << "  " << "\033[0m";
            }
        }
        cout << endl;
    }
}

void SnakeGame::Input()
{
    if (_kbhit())
    {
        char input = _getch();
        snake.ChangeDirection(input);
    }
}

void SnakeGame::Update()
{
    snake.Move(1);

    if (snake.CheckCollision(width, height)) 
    {
        isRunning = false;
        cout << "Game Over! You hit the wall or yourself!" << endl;
    }

    if (snake.GetHead().first == apple.GetX() && snake.GetHead().second == apple.GetY()) 
    {
        apple.Interact(snake, isRunning);

        vector<pair<int, int>> occupied = snake.GetBody();

        apple.RandomisePosition(width, height, occupied);
    }

    if (snake.GetHead().first == dangerZone.GetX() && snake.GetHead().second == dangerZone.GetY()) 
    {
        dangerZone.Interact(snake, isRunning);
    }
}