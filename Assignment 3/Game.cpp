#define _GLIBCXX_USE_C99 1
#include "Game.hpp"
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

Game::Game(int argc, char* argv[]) { // constructor takes 2 arguments (the command line arguments, that us)
	checkArg(argc, argv); //constructor calls checkArg() which assigns the command line arguments to the proper Game-Class attributes
}

void Game::delayBy(float f, Timer* t, bool b) { //function to delay the game by a float f of seconds. If bool b = true the game will also call the clearScreen() function
	t->start();
	while (t->elapsedSecs() < f) {
		//delay the game
	}
	t->stop();
	if (b) {
		clearScreen();
	}
}



//global functions
void Game::clearScreen() { //using ANSI escape codes to clear screen
	cout << "\033[2J\033[1;1H";
}

void Game::checkArg(int argc, char* argv[]) { //takes in command line arguments
	int rounds;
	int roundTime;
	if (argc < 4) { //if the user inputs less than 4 arguments the game will exit
		cout << "Invalid command line arguments. Usage: ./game PlayerName Rounds RoundDuration" << endl;
		exit(EXIT_FAILURE);
	}
	setPlayerName(argv[1]); //setting player name

	try {
		rounds = std::stoi(argv[2]); //if it is not possible to convert the 2nd (3rd) command line argument to an integer the game wille ecit
	}
	catch (...) {
		cout << "You must  input a number for the rounds to be played!" << endl;
		exit(EXIT_FAILURE);
	}

	if (rounds > 0) { //checks if the user has entered a positive number greater than 0 for the amount of rounds to be played
		setGameRounds(rounds); //setting rounds to be played
	}
	else {
		cout << "You must input a number greater than 0\nfor the number of rounds that you wish to play!" << endl;
		exit(EXIT_FAILURE);
	}

	try {
		roundTime = std::stoi(argv[3]); // same as above but for round duration
	}
	catch (...) {
		cout << "You must input a number for the round duration!" << endl;
		exit(EXIT_FAILURE);
	}

	if (roundTime > 0) {
		setGameTime(roundTime); // same as above but for round duration
	}
	else {
		cout << "You must input a number greater than 0 for the round duration!" << endl;
		exit(EXIT_FAILURE);
	}
}

void Game::presentWelcomeMessage() { //using string concatenation to present the user witha personalised welcome message at the beginning of the game
	cout << welcomeMessage1 << getPlayerName() << "!" << endl;
}

//      setters -> self explanatory
void Game::setGameTime(int i) { gameTime = i; }
void Game::incrementRoundCount() { ++currentRound; }
void Game::setGameRounds(int i) { gameRounds = i; }
void Game::setPlayerName(std::string n) { pName = n; }


//      getters -> self explanatory
int Game::getGameTime() { return gameTime; }
int Game::getGameRounds() { return gameRounds; }
int Game::getCurrentRound() { return currentRound; }
std::string Game::getPlayerName() { return pName; }
