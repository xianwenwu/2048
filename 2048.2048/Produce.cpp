#include "Produce.h"

Produce::Produce(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	generate_random_tile(2);
}

void Produce::generate_random_tile(){
	generate_random_tile(1);
}

void Produce::generate_random_tile(int num_to_generate){
    vector<pair<int, int>> empty_cells;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }

    if (empty_cells.empty()) {
        return;
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(empty_cells.begin(), empty_cells.end(), g);

    int count = 0;
    for (const auto& cell : empty_cells) {
        if (count >= num_to_generate) {
            break;
        }
        int val = (rand() % 2 + 1) * 2; // 2 or 4
        board[cell.first][cell.second] = val;
        count++;
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
}00
