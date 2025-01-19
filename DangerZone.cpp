#include "DangerZone.h"

void DangerZone::Interact(Snake& snake, bool& isRunning)
{
	isRunning = false;
	std::cout << "Game Over! You hit a danger zone!" << std::endl;
}