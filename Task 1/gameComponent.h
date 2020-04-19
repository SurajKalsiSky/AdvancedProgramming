#pragma once
#include <iomanip>

class GameComponent {
	public:
		GameComponent() {
			id = ++instances;
		};
		virtual void Update(const tm* time) {
			std::cout << "ID : " << id << " Updated @ " << std::put_time(time, "%X") << std::endl; // print the id and current time
		};
	private:
		int id = 0;
		static int instances;
};

int GameComponent::instances;