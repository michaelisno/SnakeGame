#include <iostream>
#include <thread>
#include "SnakeGame.h"

using namespace std;

int main()
{
	SnakeGame game(20, 20);

	while (game.Running())
	{
		game.Render();
		game.Input();
		game.Update();

		this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}