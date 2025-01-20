#pragma once
#include "Snake.h"
#include "Apple.h"
#include "DangerZone.h"
#include "PowerUp.h"
#include "GameSettings.h"
#include <ctime>
#include <vector>
#include <utility>
#include <conio.h>

class SnakeGame
{
private:
	int width, height;

    int gameUpdateRate;

	Snake snake;
	Apple apple;
	std::vector<DangerZone> dangerZones;
    std::vector<PowerUp> powerUps;

public:
    bool isRunning;

    SnakeGame(GameSettings settings) : width(settings.GameWidth), height(settings.GameHeight), isRunning(true), snake(settings.SnakeStartCoordX, settings.SnakeStartCoordY), apple(0, 0), gameUpdateRate(settings.GameUpdateRate)
    {
        srand(time(0));

        std::vector<std::pair<int, int>> occupied = snake.GetBody();

        apple.RandomisePosition(width, height, occupied);

        for (int i = 0; i < settings.NumberOfDangerZones; i++) 
        {
            DangerZone newDangerZone(0, 0);
            newDangerZone.RandomisePosition(width, height, occupied);

            dangerZones.push_back(newDangerZone);
        }

        for (int i = 0; i < settings.NumberOfPowerUps; i++)
        {
            PowerUp newPowerUp(0, 0);
            newPowerUp.RandomisePosition(width, height, occupied);

            powerUps.push_back(newPowerUp);
        }
    }

	void Render() const;
	void Input();
	void Update();

    void GameEnded(int ending);

    bool CheckHighScore(int score, int &prevHighScore);

};