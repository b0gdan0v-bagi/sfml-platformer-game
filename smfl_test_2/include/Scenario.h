#ifndef SCENARIO_H
#define SCENARIO_H

#include "SFML/Graphics.hpp"

using namespace sf;

struct Scenario
{
	int id;
	bool active;
	std::vector<std::pair<float, bool>> timer;
	//std::vector<float> timer = { 0,0,0,0,0,0,0,0,0 };
	void set(int ID) {
		id = ID; active = true; timer.resize(10); zeroTimer();
	}
	void reGlobalLoad() { id = 0; active = false; zeroTimer();
	}
	void stop() { id = 0; active = false; zeroTimer();
	}
	void timerIncreas(float time)
	{
		for (auto i = timer.begin(); i != timer.end(); i++)
		{
			if((*i).second) (*i).first += time;
		}

	}
	void zeroTimer() {
		for (auto i = timer.begin(); i != timer.end(); i++)
		{
			(*i).first = 0;
			(*i).second = true;
		}
	}
};



#endif SCENARIO_H

