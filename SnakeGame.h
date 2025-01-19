#pragma once
#include "Snake.h"
#include "Apple.h"
#include "DangerZone.h"
#include <ctime>
#include <vector>
#include <utility>
#include <conio.h>

class SnakeGame
{
private:
	int width, height;
	bool isRunning;

	Snake snake;
	Apple apple;
	DangerZone dangerZone;

public:
	SnakeGame(int w, int h) : width(w), height(h), snake(w / 2, h / 2), apple(0, 0), dangerZone(0, 0), isRunning(true) 
	{
		srand(time(0));

		std::vector<std::pair<int, int>> occupied = snake.GetBody();

		apple.RandomisePosition(width, height, occupied);
		dangerZone.RandomisePosition(width, height, occupied);
	}

	void Render() const;
	void Input();
	void Update();

	bool Running() const { return isRunning; }

};