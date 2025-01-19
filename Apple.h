#pragma once
#include "Interactable.h"

class Apple : public Interactable
{
public:
	Apple(int xPosition, int yPosition) : Interactable(xPosition, yPosition) {}

	void Interact(Snake& snake, bool& isRunning) override;
};