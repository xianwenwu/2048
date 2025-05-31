#include "Game.h"
#include <cstdlib>

Game::Game() : A() {

}

void Game::run() {
	char ch;
	for (;;) {
		cout << "-----------------------------\n";
		for (int i = 0; i < 7; i++) {
			if (i == 2)
				cout << "|         game start         |\n";
			else if (i == 3)
				cout << "|       （space start）        |\n";
			else if (i == 4)
				cout << "|    q：quit    r：Reset Game     |\n";
			else
				cout << "|                           |\n";
		}
		cout << "-----------------------------\n";

		ch = GETCH();
		if (ch == ' ')
			break;
		else if (ch == 'q') {
			exit(0);
		}
	}

	while (true) {
		CLRSCR;
		A.print_board();
		cout << "操作：方向鍵移動，r = 重來，q = 離開\n";

		int key = GETCH();
		if (key == 'q') {
			cout << "你已離開遊戲。\n";
			break;
		}
		else if (key == 'r') {
			cout << "重新開始遊戲...\n";
			A = Produce();
			continue;
		}
		else if (key == 224 || key == -32) {
			key = GETCH();
			switch (key) {
			case 72: moveUp(); break;
			case 80: moveDown(); break;
			case 75: moveLeft(); break;
			case 77: moveRight(); break;
			}
			A.generate_random_tile();
		}

		if (isGameOver()) {
			CLRSCR;
			A.print_board();
			cout << "遊戲結束！按 r 重新開始或 q 離開。\n";
			while (true) {
				int endKey = GETCH();
				if (endKey == 'r') {
					A = Produce();
					break;
				}
				else if (endKey == 'q') {
					exit(0);
				}
			}
		}
	}
}


void Game::shiftLeft() {
	for (int i = 0; i < 4; i++) {
		int k = 0;
		for (int j = 0; j < 4; j++) {
			if (A.board[i][j] != 0) {
				A.board[i][k++] = A.board[i][j];
			}
		}
		while (k < 4) {
			A.board[i][k++] = 0;
		}
	}
}
void Game::mergeLeft() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j + 1]) {
				A.board[i][j] *= 2;
				A.board[i][j + 1] = 0;
			}
		}
	}
}
void Game::moveLeft() {
	shiftLeft();
	mergeLeft();
	shiftLeft();
}
void Game::shiftRight() {
	for (int i = 0; i < 4; i++) {
		int k = 3;
		for (int j = 3; j >= 0; j--) {
			if (A.board[i][j] != 0) {
				A.board[i][k--] = A.board[i][j];
			}
		}
		while (k >= 0) {
			A.board[i][k--] = 0;
		}
	}
}
void Game::mergeRight() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (A.board[i][j] != 0 && A.board[i][j] == A.board[i][j - 1]) {
				A.board[i][j] *= 2;
				A.board[i][j - 1] = 0;
			}
		}
	}
}
void Game::moveRight() {
	shiftRight();
	mergeRight();
	shiftRight();
}
void Game::shiftUp() {
	for (int j = 0; j < 4; j++) {
		int k = 0;
		for (int i = 0; i < 4; i++) {
			if (A.board[i][j] != 0) {
				A.board[k++][j] = A.board[i][j];
			}
		}
		while (k < 4) {
			A.board[k++][j] = 0;
		}
	}
}
void Game::mergeUp() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (A.board[i][j] != 0 && A.board[i][j] == A.board[i + 1][j]) {
				A.board[i][j] *= 2;
				A.board[i + 1][j] = 0;
			}
		}
	}
}
void Game::moveUp() {
	shiftUp();
	mergeUp();
	shiftUp();
}
void Game::shiftDown() {
	for (int j = 0; j < 4; j++) {
		int k = 3;
		for (int i = 3; i >= 0; i--) {
			if (A.board[i][j] != 0) {
				A.board[k--][j] = A.board[i][j];
			}
		}
		while (k >= 0) {
			A.board[k--][j] = 0;
		}
	}
}
void Game::mergeDown() {
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i > 0; i--) {
			if (A.board[i][j] != 0 && A.board[i][j] == A.board[i - 1][j]) {
				A.board[i][j] *= 2;
				A.board[i - 1][j] = 0;
			}
		}
	}
}
void Game::moveDown() {
	shiftDown();
	mergeDown();
	shiftDown();
}
bool Game::isGameOver() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (A.board[i][j] == 0) {
				return false;
			}
			if (i > 0 && A.board[i][j] == A.board[i - 1][j]) {
				return false;
			}
			if (j > 0 && A.board[i][j] == A.board[i][j - 1]) {
				return false;
			}
		}
	}
	return true;
}
