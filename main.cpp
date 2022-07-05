#include <iostream>

#include "tic_tac_toe.h"

//it's simple program
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Welcome to tic tac toe\n";

	tic_tac_toe game;

	game.start_game();

	getchar(); getchar();
	return 0;
}