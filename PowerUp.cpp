#include "PowerUp.h"

void PowerUp::Interact(Snake& snake, bool& isRunning)
{
	srand(time(0));

	if (snake.GetCurrentPowerUp() == 0)
	{
		snake.SetPowerUp(rand() % 3 + 1);
		snake.SetPowerUpTimer(10);
	}
}