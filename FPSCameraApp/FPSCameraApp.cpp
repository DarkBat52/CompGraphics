// FPSCameraApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "FPSCamGame.h"


int main()
{
	FPSCamGame* game = new FPSCamGame();

	game->Run();

	delete game;
}


