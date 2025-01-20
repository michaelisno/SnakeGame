#pragma once
#include <utility>

struct GameSettings
{
	int NumberOfDangerZones;
	int NumberOfPowerUps;

	int GameWidth;
	int GameHeight;
	int GameUpdateRate;

	int SnakeStartCoordX;
	int SnakeStartCoordY;

	GameSettings(int numZones = 1, int width = 20, int height = 20, int updateRate = 100, int startX = 10, int startY = 10, int numPowerUps = 2)
	{
		NumberOfDangerZones = numZones;
		NumberOfPowerUps = numPowerUps;
		GameWidth = width;
		GameHeight = height;
		GameUpdateRate = updateRate;
		SnakeStartCoordX = startX;
		SnakeStartCoordY = startY;
	}

};