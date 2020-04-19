#pragma once
#include "GameComponent.h"
#include <thread>

int NO_OF_UPDATES = 5;

typedef void (*FP)(); // typedef representing a type of function that returns void and has no parameters

class Game {
	public:
		Game(int maxComponents) {}; // not mentioned how maxComponents should be used in design
		void Add(GameComponent* gameComponent) {
			components[componentCount++] = gameComponent; // add gameComponent on components array and increments counter
		};
		void Run();
		void SetInitialise(FP init) { initialise = init; }; // set init function pointer to the local initialise function pointer
		void SetTerminate(FP term) { terminate = term; }; // same as above but for terminate
	private:
		GameComponent* components[2]; // initialise game component array
		int componentCount = 0;
		FP initialise; // initialise function pointer
		FP terminate; // terminate function pointer
		const int TICKS_1000MS = 1000;
};

void Game::Run() {
	initialise();
	for (int i = 0; i < NO_OF_UPDATES; i++) {
		for (int i = 0; i < componentCount; i++) {
			auto currentTime = chrono::system_clock::now();
			auto inTimeT = chrono::system_clock::to_time_t(currentTime);
			tm* time = localtime(&inTimeT);
			components[i]->Update(time); // invoke conponent's update function with current time

		}
		chrono::milliseconds sleep(TICKS_1000MS);
		this_thread::sleep_for(sleep); // update once every second
	}
	terminate();
};