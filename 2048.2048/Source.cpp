#include "Game.h"
#include <cstdlib> // For srand, exit
#include <ctime>   // For time

int main() {
    srand(static_cast<unsigned int>(time(0))); // 僅在 main 函數中設置一次亂數種子

    Game game; // 直接創建 Game 物件，Produce 物件在 Game 內部創建並初始化
    game.run(); // 啟動遊戲主循環

    return 0;
}
