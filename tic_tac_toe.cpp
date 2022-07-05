#include "tic_tac_toe.h"
#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <string>
#include <ctime>
#include <cstdlib>

//it's simple program
using namespace std;

//constructor
tic_tac_toe::tic_tac_toe(int size_) : size(size_)
{
	srand(time(NULL));
	map_created = false;
}

//destructor
tic_tac_toe::~tic_tac_toe()
{
	// free memory
	if (map_created)
	{
		for (int i = 0; i < size_rows; i++)
		{
			delete[] * (map + i);
		}
		delete[] map;
	}
}

void tic_tac_toe::ask_map_size()
{
	string size_;
	bool condition = false;
	do
	{
		cout << "How big should be the map (only odd numbers): ";
		cin >> size_;

		int size__ = stoi(size_);

		if (size__ > 2 && size__ % 2 != 0 && size__ <= 11)
		{
			condition = true;
			size = size__;

		}
		
		if (size__ > 11)
		{
			cout << "It's too big!";
		}
		cout << endl;
		
	} while (!condition);

	size_rows = size + 3; //bounds of map and numbers of rows
	size_cols = size + 4; //bounds of map and letters which indicate columns
}

void tic_tac_toe::clear_map()
{
	for (int i = 0; i < size_rows; i++)
	{
		for (int j = 0; j < size_cols; j++)
		{
			if (i == 0 && j > 2 && j < size_cols - 1)
			{
				map[i][j] = char(int('A') + j - 3);
			}
			else if (j == 0 && i > 1 && i < size_rows - 1)
			{
				if (i - 1 < 10)
				{
					map[i][j] = char(int('0') + i - 1);
					map[i][j + 1] = ' ';
				}
					
				else // i < 100
				{
					int dec = (i-1)/10;
					int units = (i-1) % 10;
					
					map[i][j] = char(int('0') + dec);
					map[i][j+1] = char(int('0') + units);
				}
			}
			else if ((i == 1 || (i == size_rows-1)) && (j > 1) && (j < size_cols-1))
			{
				map[i][j] = '-';
			}
			else if ((j == 2 ||  (j == size_cols-1)) && (i > 1) && (i < size_rows-1))
			{
				map[i][j] = '|';
			}
			else if (!( j == 1 &&  i > 1 && i < size_rows-1))
			{
				map[i][j] = ' ';
			}
			
		}
	}
}

void tic_tac_toe::start_game()
{
	//'x' or 'o'?
	turn = rand() % 2;

	//ask for map size
	ask_map_size();

	//create map
	map = new char*[size_rows]; //create rows

	for (int i = 0; i < size_rows; i++)
		*(map + i) = new char[size_cols]; // create cols
	
	map_created = true;
	//create bounds and clear map.
	clear_map();
	
	do 
	{
		execute_move();

		//move executed -> change turn!
		turn = !turn;
	} while (!check_winner());
	
	if (check_winner())
	{
		draw_map();
		cout << "WINNER!!!!!\n\n";
		if (turn) //opposite meaning of turn!
			cout << "Congrats 'o'!\n";
		else
			cout << "Congrats 'x'!\n";

		getchar(); getchar();
	}

	cout << "Do you wanna play again?\n";
	cout << "(y\\n): ";
	char again = 0;
	cin >> again;
	if (again == 'y')
		start_game();
	else
		exit(0);
}

void tic_tac_toe::draw_map()
{
	system("cls");
	cout << "To quit type: quit.\n";

	/*CONSOLE FONT*/
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	cout << "\t\t";
	if (turn)
	{
		cout << "your turn: x\n\n";
	}
	else
	{
		cout << "your turn: o\n\n";
	}
	
	//darawing map
	for (int i = 0; i < size_rows; i++)
	{
		cout << "\t\t";
		for (int j = 0; j < size_cols; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}

	//draw actual player turn
	cout << "\n\nPosition (Col, Row) e.g. A1\n";
	cout << "Your move: ";
}

bool tic_tac_toe::check_winner()
{
	bool found = true;
	char tmp;

	if (turn) // 'x'
		tmp = 'o';
	else
		tmp = 'x';

	//check rows
	for (int row = 2; row < size_rows - 1; row++)
	{
		found = true;
		for (int col = 3; col < size_cols - 1; col++)
		{
			if (map[row][col] != tmp)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}

	//check cols
	if (!found)
	for (int col = 3; col < size_cols - 1; col++)
	{
		found = true;
		for (int row = 2; row < size_rows - 1; row++)

		{
			if (map[row][col] != tmp)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}

	//check diagonal
	if (!found)
	for (int i = 0; i < size; i++)
	{
		found = true;

		if (map[i + 2][i + 3] != tmp)
		{
			found = false;
			break;
		}
		//0,1,2
		// map[2][3]
		//map [3][4]
		//map[4][5]
	}

	if (!found)
	for (int i = 0; i < size; i++)
	{
		found = true;

		if (map[i + 2][size + 2 - i] != tmp)
		{
			found = false;
			break;
		}
	}
	
	if (found)
		return true;
	else
		return false;
}

void tic_tac_toe::execute_move()
{
	bool isDataCorrect = false;
	int row_ = 0;
	int col_ = 0;

	do
	{
		draw_map();

		string a;
		cin >> a;

		//col name
		for (auto & x : a)
		{
			x = toupper(x);
		}

		if (a == "QUIT")
		{
			exit(EXIT_SUCCESS);
		}

		if (a.size() == 2)
		{
			col_ = a[0] - 'A';
			row_ = a[1] - '0';
			if (a[0] >= 'A' && a[0] <= 'Z' && row_ > 0 && row_ <= size)
			if (row_ <= size && row_ >= 0 && col_ <= size && col_ >= 0)
				if(map[row_ + 1][col_ + 3] == ' ')
					isDataCorrect = true;
		}
		//for bigger maps
		else if (a.size() == 3)
		{
			col_ = a[0] - 'A';
			int row_0 = a[1] - '0';
			int row_1 = a[2] - '0';
			row_ = row_0 * 10 + row_1;
			if (a[0] >= 'A' && a[0] <= 'Z' && row_ > 0 && row_ <= size)
			if (row_ <= size && row_ >= 0 && col_ <= size && col_ >= 0 )
				if(map[row_ + 1][col_ + 3] == ' ')
					isDataCorrect = true;
		}

		if (!isDataCorrect)
		{
			if (row_ <= size && row_ >= 0 && col_ <= size && col_ >= 0)
			{
				if (map[row_ + 1][col_ + 3] != ' ')
					cout << "This place is not free!!!\n Try again!\n";
			}
			else
				cout << "Wrong data!!!\n\n";
			Sleep(1500);
		}
	} while (!isDataCorrect);
	
	if (turn) // -> 'x'
	{
		map[row_ + 1][col_ + 3] = 'x';
	}
	else // -> 'o'
	{
		map[row_ + 1][col_ + 3] = 'o';
	}
}