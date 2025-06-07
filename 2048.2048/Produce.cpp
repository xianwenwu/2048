#include "Produce.h"
#include <windows.h>

Produce::Produce() {
    srand(static_cast<unsigned int>(time(0)));
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

void Produce::generate_random_tile() {
    srand(static_cast<unsigned int>(time(0)));
    int amount = (rand() % 2 + 1);
    int empty = 0;
    int place[2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) empty++;
        }
    }
    if (empty == 1)
        amount = 1;

    if (amount == 1) {
        place[0] = -1;
        place[1] = (rand() % empty);
    }
    else {
        place[0] = (rand() % empty);
        place[1] = place[0];
        while (place[0] == place[1]) place[1] = (rand() % empty);
    }
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                if (count == place[0] || count == place[1]) {
                    board[i][j] = ((rand() % 2 + 1)) * 2;
                }
                count++;
            }
        }
    }
}

void Produce::print_board(HANDLE hConsole) {
    cout << "\n2048\n";
    cout << "-----------------------------\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int value = board[i][j];
            int color = 7;
            switch (value) {
                case 0:    color = 8;  break;
                case 2:    color = 7;  break;
                case 4:    color = 15; break;
                case 8:    color = 14; break;
                case 16:   color = 11; break;
                case 32:   color = 13; break;
                case 64:   color = 10; break;
                case 128:  color = 9;  break;
                case 256:  color = 12; break;
                default:   color = 12; break;
            }
            SetConsoleTextAttribute(hConsole, 7);
            cout << "|";
            SetConsoleTextAttribute(hConsole, color);
            cout << " " << setw(4) << (value == 0 ? "." : to_string(value)) << " ";
            SetConsoleTextAttribute(hConsole, 7);
        }
        cout << "|\n";
        cout << "-----------------------------\n";
    }
}
