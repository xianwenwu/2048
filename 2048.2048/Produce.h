#ifndef R_H
#define R_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string>
#include<windows.h>
using namespace std;

class Produce
{
public:
	int board[4][4];
	Produce();
	void generate_random_tile();
	void print_board(HANDLE hConsole);
};
#endif
