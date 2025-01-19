#pragma once
#include "Interactable.h"
#include <iostream>

class DangerZone : public Interactable
{
public:
	DangerZone(int xPosition, int yPosition) : Interactable(xPosition, yPosition) {}

	void Interact(Snake& snake, bool& isRunning) override;
};