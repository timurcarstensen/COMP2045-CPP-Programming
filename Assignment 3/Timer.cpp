#include "Timer.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void Timer::start() {
	timerStartTime = std::chrono::system_clock::now();
	timerRunning = true;
}

void Timer::stop() {
	timerEndTime = std::chrono::system_clock::now(); //set the timerEndTime to now
	timerRunning = false;
}

double Timer::elapsedMS() { //returns elapsed milliseconds as double
	std::chrono::time_point<std::chrono::system_clock> endTime; //initialise a time point based on the system clock named endTime

	if (timerRunning) { //if the timer is running set endTime to now
		endTime = std::chrono::system_clock::now();
	}
	else { //else (the timer is not running) set endTime to the attribute timerEndTime
		endTime = timerEndTime;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - timerStartTime).count(); //return endTime - timerStartTime to determine how many ms have passed
}

double Timer::elapsedSecs() { //returns elapsed seconds as double
	return elapsedMS() / 1000;
}

