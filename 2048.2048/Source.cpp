#include"Game.h"
#include<ctime>
#include<cstdlib>

int main() {
	srand(static_cast<unsigned int>(time(0)));
	Produce p;
	Game play(p);
	play.play();
}
