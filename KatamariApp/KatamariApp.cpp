// KatamariApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "KatamariGame.h"

#include <iostream>

using namespace std;

int main()
{
	int a;
	//cin >> a;

	KatamariGame* game = new KatamariGame();

	game->Run();

	delete game;
}


