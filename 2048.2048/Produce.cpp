#include "Produce.h"

Produce::Produce(){
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	// �H����ܨ�Ӥ��P��m�ө�J��l���Ʀr 2
	int place1 = (rand() % 16); // �� 1 ���H����m�]0~15�^
	int place2 = place1;
	while (place1 == place2) place2 = (rand() % 16); // �T�O��Ӧ�m���P

	// �N�� place1 �M place2 ����m�]�� 2
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

// �H���b�Ů椤�ͦ� 1~2 �ӷs������]�Ȭ� 2 �� 4�^
void Produce::generate_random_tile(){
	srand(static_cast<unsigned int>(time(0)));// �]�w�üƺؤl
	int amount = (rand() % 2 + 1); // �o���n���ʹX�� tile�]1 �� 2�^
	int empty = 0;// �����Ů檺�ƶq
	int place[2]; // �����n��m�s tile ����m

	// �p��Ů��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) empty++;
		}
	}
	// �p�G�u�ѤU�@��Ů�A�u���ͤ@�� tile
	if (empty == 1)
		amount = 1;
	// �M�w�n�b���ǪŮ��m���ͷs tile
	if (amount == 1) {
		place[0] = -1;
		place[1] = 0;
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < 1; j++) {
				if (board[i][j] == 0) place[1] = 4 * i + j;
			}
		}
	}
	// �H����X��Ӥ��P���Ů���ަ�m
	else {
		place[0] = (rand() % empty);
		place[1] = place[0];
		while (place[0] == place[1]) place[1] = (rand() % empty);
	}
	// �N�H���襤���Ů�]�� 2 �� 4
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

// ��X�ثe���ѽL���A��e��
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
