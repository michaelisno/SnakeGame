#include "PowerUp.h"


void PowerUp::Interact(Snake& snake, bool& isRunning)
{
	srand(time(0));

	// snake currently has no power ups
	if (snake.GetCurrentPowerUp() == 0)
	{
		// set random power up
		snake.SetPowerUp(rand() % 3 + 1);
		snake.SetPowerUpTimer(10);
	}
}