#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include "Timer.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Game {
public:

	Game(int argc, char* argv[]);

	void endGame();
	void delayBy(float f, Timer* t, bool b);
	void clearScreen();
	void checkArg(int argc, char* argv[]);
	void presentWelcomeMessage();


	//  setters
	void setGameTime(int i);
	void incrementRoundCount();
	void setGameRounds(int i);
	void setPlayerName(std::string n);

	//    getters
	int getGameTime();
	int getGameRounds();
	int getCurrentRound();
	std::string getPlayerName();

private:

	//integers
	int gameTime;
	int gameRounds;
	int currentRound = 0;

	//string
	std::string pName;
	std::string welcomeMessage1 = "Welcome to the wordGuessing Game, ";

	//booleans
	bool gameRunning = false;
};



#endif /* Game_hpp */
