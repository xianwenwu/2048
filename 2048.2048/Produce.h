#ifndef R_H
#define R_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include <vector>
#include <algorithm>
#include <random> // For std::mt19937

using namespace std;

class Produce
{
public:
	int board[4][4];
	Produce();
	void generate_random_tile();
	void print_board();
};
#endif
