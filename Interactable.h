#pragma once
#include <vector>
#include <utility>
#include "Snake.h"
#include <string>

class Interactable
{
protected:
	int m_xPosition, m_yPosition;

public:
	Interactable(int xPosition, int yPosition) { m_xPosition = xPosition; m_yPosition = yPosition; }

	void RandomisePosition(int width, int height, const std::vector<std::pair<int, int>> &occupied);

	virtual void Interact(Snake& snake, bool& isRunning) = 0;

	int GetX() const { return m_xPosition; }
	int GetY() const { return m_yPosition; }
};