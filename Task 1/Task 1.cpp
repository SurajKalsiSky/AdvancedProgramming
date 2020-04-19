#define _CRT_SECURE_NO_WARNINGS // needed as using localtime not localtime_s in game.h
#include <iostream>
#include "gameComponent.h"
#include "drawableGameComponent.h"
#include "game.h"

using namespace std;

void initialise() {
	cout << "Initialising game..." << endl;
};

void terminate() {
	cout << "Terminating game..." << endl;
};

int main() {
	Game game(NULL); // setting maxComponents to NULL as not used in game class
	game.SetInitialise(*initialise);
	game.SetTerminate(*terminate);

	GameComponent* gameComponent = new GameComponent();
	game.Add(gameComponent);

	DrawableGameComponent* drawableGameComponent = new DrawableGameComponent(0, 0);
	game.Add(drawableGameComponent);

	game.Run();
}
