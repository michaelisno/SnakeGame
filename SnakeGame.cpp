#include "SnakeGame.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>

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

            for (DangerZone zone : dangerZones)
            {
                if (zone.GetX() == x && zone.GetY() == y && !printed)
                {
                    cout << "\033[41m  \033[0m";
                    printed = true;
                    break;
                }
            }

            for (PowerUp powerUp : powerUps)
            {
                if (powerUp.GetX() == x && powerUp.GetY() == y && !printed)
                {
                    cout << "\033[46m  \033[0m";
                    printed = true;
                    break;
                }
            }

            if (!printed) 
            {
                cout << "\033[48;5;235m" << "  " << "\033[0m";
            }
        }
        cout << endl;
    }

    cout << "Current Length: " << snake.GetBody().size() << " | Active Power-Up: ";

    if (snake.GetCurrentPowerUp() == 0) cout << "None";
    else if (snake.GetCurrentPowerUp() == 1) cout << "Increased Movement Speed";
    else if (snake.GetCurrentPowerUp() == 2) cout << "Increased Growth Amount";
    else if (snake.GetCurrentPowerUp() == 3) cout << "Invincibility";

    if (snake.GetCurrentPowerUp() != 0)
        cout << " For: " << snake.GetPowerUpTimer() << " more second(s)." << endl;
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
    if (snake.GetCurrentPowerUp() == 1)
        snake.Move(2);
    else
        snake.Move(1);

    static int elapsedTime = 0;

    // snake power up count-down timer
    if (snake.GetCurrentPowerUp() != 0)
    {
        if (snake.GetPowerUpTimer() == 0)
        {
            // power-up finished
            elapsedTime = 0;
            snake.SetPowerUp(0);
            snake.SetPowerUpTimer(10);
        }
        else {
            elapsedTime += gameUpdateRate;
            if (elapsedTime >= 1000)
            {
                snake.SetPowerUpTimer(snake.GetPowerUpTimer() - 1);
                elapsedTime -= 1000;
            }
        }
    }

    if (snake.CheckCollision(width, height))
    {
        isRunning = false;
        GameEnded(1);
    }

    if (snake.GetHead().first == apple.GetX() && snake.GetHead().second == apple.GetY()) 
    {
        apple.Interact(snake, isRunning);

        vector<pair<int, int>> occupied = snake.GetBody();

        apple.RandomisePosition(width, height, occupied);
    }

    if (snake.GetCurrentPowerUp() != 3)
    {
        for (DangerZone dangerZone : dangerZones)
        {
            if (snake.GetHead().first == dangerZone.GetX() && snake.GetHead().second == dangerZone.GetY())
            {
                dangerZone.Interact(snake, isRunning);

                if (!isRunning)
                    GameEnded(2);
            }
        }
    }

    if (snake.GetCurrentPowerUp() == 0)
    {
        for (auto it = powerUps.begin(); it != powerUps.end();)
        {
            if (snake.GetHead().first == it->GetX() && snake.GetHead().second == it->GetY())
            {
                it->Interact(snake, isRunning);
                it = powerUps.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void SnakeGame::GameEnded(int ending)
{
    system("cls");

    cout << "Snake Game" << endl << "----------" << endl << endl;

    if (ending == 1)
        cout << "Game Over! You hit a wall or yourself!" << endl;
    else if (ending == 2)
        cout << "Game Over! You hit a danger zone!" << endl;

    cout << "Your Snake was: " << snake.GetBody().size() << " segment(s) long." << endl;

    int prevHighScore = 0;

    if (CheckHighScore(snake.GetBody().size(), prevHighScore))
    {
        cout << "Previous High Score: " << prevHighScore << "." << endl;
        cout << "You beat the high score!" << endl;
    }

    cout << endl;
    cout << "Play Again? Press any key.";

    while (!_kbhit())
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    system("start x64/Debug/SnakeGame.exe");
}

bool SnakeGame::CheckHighScore(int score, int &prevHighScore)
{
    int highScore;

    ifstream file("high_score.txt");

    if (file.is_open())
    {
        file >> highScore;
        prevHighScore = highScore;
        file.close();
    }

    if (score > highScore)
    {
        ofstream file("high_score.txt");

        if (file.is_open())
        {
            file << score;
            file.close();
        }

        return true;
    }

    return false;
}