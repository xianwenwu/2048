#ifndef R_H
#define R_H

#include <iostream>
#include <iomanip>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <vector>  // For std::vector
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937

class Produce {
public:
    int board[4][4];
    Produce(); // 初始化遊戲面板
    void generate_random_tile_one_or_two(); // 隨機產生 1 或 2 個方塊
    void generate_random_tile(int count); // 產生指定數量的方塊
    void print_board(); // 印出初始畫面、更新後畫面
};

#endif
