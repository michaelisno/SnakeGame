#pragma once
#include "Interactable.h"
#include <ctime>

class PowerUp : public Interactable
{
public:
	PowerUp(int xPosition, int yPosition) : Interactable(xPosition, yPosition) {}

	void Interact(Snake& snake, bool& isRunning) override;
};