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
	int m_width, m_height;
    int m_gameUpdateRate;

    bool m_isRunning;

	Snake snake;
	Apple apple;

	std::vector<DangerZone> dangerZones;
    std::vector<PowerUp> powerUps;

public:
    SnakeGame(GameSettings settings) : m_width(settings.GameWidth), m_height(settings.GameHeight), m_isRunning(true), snake(settings.SnakeStartCoordX, settings.SnakeStartCoordY), apple(0, 0), gameUpdateRate(settings.GameUpdateRate)
    {
        srand(time(0));

        std::vector<std::pair<int, int>> occupied = snake.GetBody();

        apple.RandomisePosition(m_width, m_height, occupied);

        for (int i = 0; i < settings.NumberOfDangerZones; i++) 
        {
            DangerZone newDangerZone(0, 0);
            newDangerZone.RandomisePosition(m_width, m_height, occupied);

            dangerZones.push_back(newDangerZone);
        }

        for (int i = 0; i < settings.NumberOfPowerUps; i++)
        {
            PowerUp newPowerUp(0, 0);
            newPowerUp.RandomisePosition(m_width, m_height, occupied);

            powerUps.push_back(newPowerUp);
        }
    }

	void Render() const;
	void Input();
	void Update();
    void GameEnded(int ending);

    bool CheckHighScore(int score, int &prevHighScore);

    bool GetIsRunning() const { return m_isRunning; }
    void SetIsRunning(bool isRunning) { m_isRunning = isRunning; }

    int GetUpdateRate() const { return m_gameUpdateRate; }
    void SetUpdateRate(int updateRate) { m_gameUpdateRate = updateRate; }
};