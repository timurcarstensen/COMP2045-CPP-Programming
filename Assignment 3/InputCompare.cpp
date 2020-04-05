#include "InputCompare.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int InputCompare::determineHealthPointsToLoose(float p) {

	if (p == 100) {
		return 0;
	}
	else if (p < 80 && p > 60) {
		return 1;
	}
	else if (p < 60 && p > 40) {
		return 2;
	}
	else if (p < 40 && p > 20) {
		return 3;
	}
	else if (p < 20 && p >= 1) {
		return 4;
	}
	else {
		return 5;
	}
}

float InputCompare::fuzzyComparison() {  //my algorithm from Coursework 2
	if (answerptr->size() != userInputptr->size()) {
		addSpaces(answerptr, userInputptr); //adding spaces so that the size of the correct answer and the size of user input are at least always the same length. Else the algorithm will return an error
	}

	int count = 0;
	int times = 0;
	maxScore = int(answer.length());
	std::string similarString = "";
	std::string tempString = "";

	for (int i = 0; i <= answer.length() - userInput.length(); i++) {
		int j;
		times = 0;
		tempString = "";

		for (j = 0; j < userInput.length(); j++) {

			if (answer[i + j] == userInput[j]) {
				times++;
			}
			tempString += answer[i + j];
		}

		if (times > count) {
			count = times;
			similarString = tempString;
		}
	}

	scorePercentage = (float(count) / float(maxScore)); //instead of returning the most similar string (like in CW2), the algorithm rates the user input on how closely it matches it matches the correct answer and returns a percentage which is then returned as scorePercentage
	return scorePercentage;
}

void InputCompare::setAnswer(std::string n) { //takes in the correct answer and transforms to lower and removes leading & trailing whitespace
	n = removeWhitespace(n);
	n = toLower(n);
	answer = n;
}

void InputCompare::setInput(std::string n) { //takes in user input and transforms to lower and removes leading & trailing whitespace
	n = removeWhitespace(n);
	n = toLower(n);
	userInput = n;
}

std::string InputCompare::toLower(std::string str) { //using std::transform and ::tolower to convert the string to all lower characters
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string InputCompare::removeWhitespace(std::string str) { //using a regular expression to remove all leading and trailing whitespace from the passed in string
	str = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
	return str;
}

void InputCompare::addSpaces(std::string * original, std::string * in) {  //adds spaces to "in" as long as its size is lower than "originals"
	while (original->size() < in->size()) {
		*original += " ";
	}
}
