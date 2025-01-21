#include "Apple.h"

void Apple::Interact(Snake &snake, bool &isRunning) 
{
	if (snake.GetCurrentPowerUp() == 2)
	{
		snake.AddBodySegment(2);
		return;
	}

	snake.AddBodySegment(1);
}