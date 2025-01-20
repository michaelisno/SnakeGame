#include <iostream>
#include <thread>
#include "SnakeGame.h"

using namespace std;

int main()
{
	GameSettings settings;

	system("cls");
	cout << "Welcome to Snake!" << endl << endl;
	cout << "Interactables:" << endl << "--------------" << endl;
	cout << "1 - Apple: " << "\033[42m  \033[0m" << " - This will grow the Snake." << endl;
	cout << "2 - Danger Zone: " << "\033[41m  \033[0m" << " - This will kill the Snake and end the game." << endl;
	cout << "3 - Power Up: " << "\033[46m  \033[0m" << " - This will give you a random power of up either speed boost, increased growing amount, or invincibility for a period of time." << endl;
	cout << "--------------" << endl << endl;
	cout << "Game Settings:" << endl << "--------------" << endl;
	cout << "Game Width: ";
	cin >> settings.GameWidth;
	cout << "Game Height: ";
	cin >> settings.GameHeight;
	cout << "Number of Danger Zones: ";
	cin >> settings.NumberOfDangerZones;
	cout << "-----------" << endl << endl;

	cout << "The game is ready, press any key to begin!" << endl;

	while (!_kbhit())
	{
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	settings.GameUpdateRate = 100;
	settings.SnakeStartCoordX = settings.GameWidth / 2;
	settings.SnakeStartCoordY = settings.GameHeight / 2;
	settings.NumberOfPowerUps = 3;

	SnakeGame game(settings);

	while (game.isRunning)
	{
		game.Render();
		game.Input();
		game.Update();

		this_thread::sleep_for(chrono::milliseconds(settings.GameUpdateRate));
	}

	return 0;
}