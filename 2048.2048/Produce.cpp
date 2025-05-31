#include "Produce.h"

Produce::Produce() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }

    // Randomly select two different positions to place the initial number 2
    int place1 = (rand() % 16); // First random position (0~15)
    int place2 = place1;
    while (place1 == place2) place2 = (rand() % 16); // Ensure the two positions are different

    // Set the values at place1 and place2 to 2
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

// Randomly generate 1~2 new tiles (values of 2 or 4) in empty spaces
void Produce::generate_random_tile() {
    srand(static_cast<unsigned int>(time(0))); // Set random seed
    int amount = (rand() % 2 + 1); // Number of tiles to generate (1 or 2)
    int empty = 0;                // Number of empty spaces
    int place[2];                 // Positions to place new tiles

    // Count empty spaces
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) empty++;
        }
    }
    // If there is only one empty space, generate only one tile
    if (empty == 1)
        amount = 1;
    // Determine which empty spaces to generate new tiles in
    if (amount == 1) {
        place[0] = -1;
        place[1] = 0;
        for (int i = 0; i < 4; i++) { // This loop only runs once, inefficient
            for (int j = 0; j < 4; j++) { // This loop should go to 4
                if (board[i][j] == 0) place[1] = 4 * i + j;
            }
        }
    }
    // Randomly select two different empty space indices
    else {
        place[0] = (rand() % empty);
        place[1] = place[0];
        while (place[0] == place[1]) place[1] = (rand() % empty);
    }
    // Set the randomly selected empty spaces to 2 or 4
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                if (count == place[0] || count == place[1]) {
                    board[i][j] = ((rand() % 2 + 1)) * 2;
                    count++;
                }
                else
                    count++;
            }
        }
    }
}

// Output the current board state to the screen
void Produce::print_board() {
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
