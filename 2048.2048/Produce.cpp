#include "Produce.h"

Produce::Produce() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    // 初始生成兩個方塊
    generate_random_tile(2);
}

void Produce::generate_random_tile_one_or_two() {
    int amount = (rand() % 2 + 1); // 這次要產生幾個 tile（1 或 2）
    generate_random_tile(amount);
}

void Produce::generate_random_tile(int count_to_generate) {
    std::vector<std::pair<int, int>> empty_cells;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }

    if (empty_cells.empty()) {
        return; // 沒有空位了
    }

    // 使用 C++11 亂數引擎
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(empty_cells.begin(), empty_cells.end(), g);

    int actual_generated_count = 0;
    for (const auto& cell : empty_cells) {
        if (actual_generated_count >= count_to_generate) {
            break;
        }
        int val = (rand() % 2 + 1) * 2; // 50% 機率 2，50% 機率 4
        board[cell.first][cell.second] = val;
        actual_generated_count++;
    }
}

void Produce::print_board() {
    std::cout << "\n2048\n";
    std::cout << "-----------------------------\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << "| " << std::setw(4) << board[i][j] << " ";
        }
        std::cout << "|\n";
        std::cout << "-----------------------------\n";
    }
}
