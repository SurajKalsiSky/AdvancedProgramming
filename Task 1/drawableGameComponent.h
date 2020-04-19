#pragma once
#include "gameComponent.h"

using namespace std;

enum Direction : unsigned char {
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4,
};

class DrawableGameComponent : public GameComponent {
	public:
		DrawableGameComponent(int X, int Y) {
			direction = Right;
			x = 0;
			y = 0;
		};
		Direction direction;
		const int SCREEN_HEIGHT = 20;
		const int SCREEN_WIDTH = 80;
		void Update(const tm* eventTime) override;
	private:
		void ChangeDirection();
		void Draw() {
			cout << currentDirection << " : " << "X:" << x << " Y:" << y << endl; // print currentDirection with x and y values
		};
		int x, y;
		string currentDirection; // used for printing the currentDirection, not in designs
};

void DrawableGameComponent::Update(const tm* eventTime) {
	GameComponent::Update(eventTime); // invoke inherited update function from GameComponent

	switch (direction) { // switch case statement for calculating new x or y value
		case Up:
			y++;
			if (y > SCREEN_HEIGHT) {
				y = SCREEN_HEIGHT;
			}
			currentDirection = "Up";
			break;
		case Down:
			y--;
			if (y < 0) {
				y = 0;
			}
			currentDirection = "Down";
			break;
		case Left:
			x--;
			if (x < 0) {
				x = 0;
			}
			currentDirection = "Left";
			break;
		case Right:
			x++;
			if (x > SCREEN_WIDTH) {
				x = SCREEN_WIDTH;
			}
			currentDirection = "Right";
			break;
		default:
			break;
	}
	Draw();
	ChangeDirection();
};

void DrawableGameComponent::ChangeDirection() {
	int randomNumber = (rand() % 4) + 1; // random number between 1 and 4

	while (randomNumber == direction) // check number is not same as current direction
		randomNumber = (rand() % 4) + 1;

	direction = static_cast<Direction>(randomNumber); // set new direction
};