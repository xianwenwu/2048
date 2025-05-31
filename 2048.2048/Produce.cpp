#include "Produce.h"

Produce::Produce(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	int place1 = (rand() % 16);
	int place2 = place1;
	while (place1 == place2) place2 = (rand() % 16);

	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (count == place1 || count == place2) {
				board[i][j] = 2;
			}
			count++;
		}
	}
}

void Produce::generate_random_tile(){
	vector<pair<int, int>> emptyCells;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				emptyCells.push_back({i, j});
			}
		}
	}

	if (emptyCells.empty()) {
		return;
	}

	int amount = (rand() % 2 + 1);
	if (emptyCells.size() == 1) {
		amount = 1;
	}

	for (int k = 0; k < amount; ++k) {
		if (emptyCells.empty()) {
			break;
		}
		int randomIndex = rand() % emptyCells.size();
		pair<int, int> cell = emptyCells[randomIndex];
		board[cell.first][cell.second] = ((rand() % 2 + 1)) * 2;
		emptyCells.erase(emptyCells.begin() + randomIndex);
	}
}

void Produce::print_board(){

	cout << "\n2048\n";
	cout << "-----------------------------\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "| " << setw(4) << board[i][j] << " ";
		}
		cout << "|\n";
		cout << "-----------------------------\n";
	}
}
