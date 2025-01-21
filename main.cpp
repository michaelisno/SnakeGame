#include <iostream>
#include <thread>
#include "SnakeGame.h"

using namespace std;

int main()
{
	GameSettings settings;
	SnakeGame game(settings);

	system("cls");

	PrintInstructions();
	SetSettings(settings);

	settings.GameUpdateRate = 100;
	settings.SnakeStartCoordX = settings.GameWidth / 2;
	settings.SnakeStartCoordY = settings.GameHeight / 2;

	cout << "-----------" << endl << endl << "The game is ready, press any key to begin!" << endl;

	while (!_kbhit())
	{
		this_thread::sleep_for(chrono::milliseconds(settings.GameUpdateRate));
	}

	while (game.GetIsRunning())
	{
		game.Render();
		game.Input();
		game.Update();

		this_thread::sleep_for(chrono::milliseconds(game.GetUpdateRate()));
	}

	return 0;
}

void PrintInstructions()
{
	cout << "Welcome to Snake!" << endl << endl;
	cout << "Interactables:" << endl;
	cout << "--------------" << endl;
	cout << "1 - Apple: " << "\033[42m  \033[0m" << " - Will grow the Snake." << endl;
	cout << "2 - Danger Zone: " << "\033[41m  \033[0m" << " - Will kill the Snake and end the game." << endl;
	cout << "3 - Power Up: " << "\033[46m  \033[0m" << " - Will give random power up of Speed Boost, Increased Growth Amount, or Invincibility for 10 seconds." << endl;
	cout << "--------------" << endl << endl;
	cout << "Game Settings:" << endl;
	cout << "--------------" << endl;
}

void SetSettings(GameSettings &settings)
{
	cout << "Game Width: ";
	cin >> settings.GameWidth;
	cout << "Game Height: ";
	cin >> settings.GameHeight;
	cout << "Number of Danger Zones: ";
	cin >> settings.NumberOfDangerZones;
	cout << "Number of Power Ups: ";
	cin >> settings.NumberOfPowerUps;
}