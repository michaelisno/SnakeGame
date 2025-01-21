#include "SnakeGame.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

void SnakeGame::Render() const
{
	system("cls");

    for (int y = 0; y < m_height; y++) 
    {
        for (int x = 0; x < m_width; x++) 
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

    if (snake.GetCurrentPowerUp() != 0) cout << " For: " << snake.GetPowerUpTimer() << " more second(s)." << endl;

}

void SnakeGame::Input()
{
    if (_kbhit())
    {
        snake.ChangeDirection(_getch());
    }
}

void SnakeGame::Update()
{  
    snake.Move();

    static int elapsedTime = 0;
    static int tempUpdateRate = 0;

    if (snake.GetCurrentPowerUp() != 0)
    {
        if (snake.GetCurrentPowerUp() == 1 && tempUpdateRate == 0)
        {
            tempUpdateRate = GetUpdateRate();
            SetUpdateRate(tempUpdateRate / 1.5);
        }

        if (snake.GetPowerUpTimer() == 0)
        {
            if (snake.GetCurrentPowerUp() == 1)
            {
                SetUpdateRate(tempUpdateRate);
                tempUpdateRate = 0;
            }

            elapsedTime = 0;

            snake.SetPowerUp(0);
            snake.SetPowerUpTimer(10);
        }
        else 
        {
            elapsedTime += GetUpdateRate();

            while (elapsedTime >= 1000)
            {
                snake.SetPowerUpTimer(snake.GetPowerUpTimer() - 1);
                elapsedTime -= 1000;
            }
        }
    }

    if (snake.CheckCollision(m_width, m_height))
    {
        SetIsRunning(false);
        GameEnded(1);
    }

    if (snake.GetHead().first == apple.GetX() && snake.GetHead().second == apple.GetY()) 
    {
        vector<pair<int, int>> occupied = snake.GetBody();

        apple.Interact(snake, m_isRunning);
        apple.RandomisePosition(m_width, m_height, occupied);
    }

    if (snake.GetCurrentPowerUp() != 3)
    {
        for (DangerZone dangerZone : dangerZones)
        {
            if (snake.GetHead().first == dangerZone.GetX() && snake.GetHead().second == dangerZone.GetY())
            {
                dangerZone.Interact(snake, m_isRunning);

                if (!GetIsRunning())
                {
                    GameEnded(2);
                }
            }
        }
    }

    if (snake.GetCurrentPowerUp() == 0)
    {
        for (auto powerUpIterator = powerUps.begin(); powerUpIterator != powerUps.end();)
        {
            if (snake.GetHead().first == powerUpIterator->GetX() && snake.GetHead().second == powerUpIterator->GetY())
            {
                powerUpIterator->Interact(snake, m_isRunning);
                powerUpIterator = powerUps.erase(powerUpIterator);
            }
            else
            {
                ++powerUpIterator;
            }
        }
    }
}

void SnakeGame::GameEnded(int ending)
{
    system("cls");

    cout << "Snake Game Over" << endl << "---------------" << endl << endl;

    if (ending == 1) cout << "Game Over! You hit a wall or yourself!" << endl;
    else if (ending == 2) cout << "Game Over! You hit a danger zone!" << endl;

    cout << "Your Snake was: " << snake.GetBody().size() << " segment(s) long." << endl;

    int prevHighScore = 0;

    if (CheckHighScore(snake.GetBody().size(), prevHighScore))
    {
        cout << "Previous High Score: " << prevHighScore << "." << endl;
        cout << "You beat the high score!" << endl;
    }

    cout << endl;
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