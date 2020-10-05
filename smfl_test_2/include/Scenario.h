#ifndef SCENARIO_H
#define SCENARIO_H

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

struct Scenario
{
	int id;
	bool active;
	std::vector<std::pair<float, bool>> timer;
	void set(int ID, int TIMERS = 10) {
		id = ID;
		active = true;
		timer.resize(TIMERS); 
		zeroTimer();
		std::cout << "Scenario " << id << " is set! Number of timers set to " << timer.size() << "\n";
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
	void zeroTimer(bool toggle = false, int TIMERS = 10) {
		timer.resize(10);
		for (auto i = timer.begin(); i != timer.end(); i++)
		{
			(*i).first = 0;
			(*i).second = toggle;
		}
		timer[0].second = true; // 1 st timer active
	}
};



#endif SCENARIO_H

