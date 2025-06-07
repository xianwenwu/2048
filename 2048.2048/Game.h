#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>
#include "Produce.h"
using namespace std;

class Game {
private:
    enum GameMode { ENDLESS, CHALLENGE };
    GameMode mode;
    string nickname;
    chrono::steady_clock::time_point startTime;
    bool winConditionMet;

    void shiftLeft();
    void mergeLeft();
    void moveLeft();
    void shiftRight();
    void mergeRight();
    void moveRight();
    void shiftUp();
    void mergeUp();
    void moveUp();
    void shiftDown();
    void mergeDown();
    void moveDown();
    bool checkWinCondition();

public:
    Produce A;
    Game(Produce);
    void play();
    bool isGameOver();
};
#endif
