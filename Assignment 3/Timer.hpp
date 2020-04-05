#ifndef Timer_hpp
#define Timer_hpp

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Timer {

public:

	void start();
	void stop();
	double elapsedSecs();

private:

	double elapsedMS();
	std::chrono::time_point<std::chrono::system_clock> timerStartTime;
	std::chrono::time_point<std::chrono::system_clock> timerEndTime;
	bool timerRunning;
};


#endif
