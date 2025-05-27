#include "Produce.h"

Produce::Produce(){
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	// 隨機選擇兩個不同位置來放入初始的數字 2
	int place1 = (rand() % 16); // 第 1 個隨機位置（0~15）
	int place2 = place1;
	while (place1 == place2) place2 = (rand() % 16); // 確保兩個位置不同

	// 將第 place1 和 place2 的位置設為 2
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

// 隨機在空格中生成 1~2 個新的方塊（值為 2 或 4）
void Produce::generate_random_tile(){
	srand(static_cast<unsigned int>(time(0)));// 設定亂數種子
	int amount = (rand() % 2 + 1); // 這次要產生幾個 tile（1 或 2）
	int empty = 0;// 紀錄空格的數量
	int place[2]; // 紀錄要放置新 tile 的位置

	// 計算空格數
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) empty++;
		}
	}
	// 如果只剩下一格空格，只產生一個 tile
	if (empty == 1)
		amount = 1;
	// 決定要在哪些空格位置產生新 tile
	if (amount == 1) {
		place[0] = -1;
		place[1] = 0;
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < 1; j++) {
				if (board[i][j] == 0) place[1] = 4 * i + j;
			}
		}
	}
	// 隨機選出兩個不同的空格索引位置
	else {
		place[0] = (rand() % empty);
		place[1] = place[0];
		while (place[0] == place[1]) place[1] = (rand() % empty);
	}
	// 將隨機選中的空格設為 2 或 4
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				if (count == place[0] || count == place[1]) {
					board[i][j] = ((rand() % 2 + 1)) * 2;
					count++;
				}
				else count++;
			}
		}
	}
}

// 輸出目前的棋盤狀態到畫面
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
