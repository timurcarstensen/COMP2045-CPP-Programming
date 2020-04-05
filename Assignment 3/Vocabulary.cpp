#include "Vocabulary.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

Vocabulary::Vocabulary() { //constructor
	loadVocabularyFile(); //calls loadVocabularyFile();
}

void Vocabulary::returnRandomQuestionFromVocabulary() { //sets a random question from the vocabulary

	if (!vocabularyLoaded) { //checks if the vocabulary has been loaded from the file yet -> if not, the game will exit
		cout << "the vocabulary hasn't been loaded yet" << endl;
		exit(EXIT_FAILURE);
	}

	if (questions.size() == answers.size()) { //checks if both vectors (questions, answers) have the same size e.g. that there is an answer for every question
		int r = randomInt(0, (int(questions.size())) - 2); //drawing a random integer using the randomInt() function

		currentQuestion = questions[r]; //accessing the questions vector via the just drawn random int
		currentAnswer = answers[r]; //same as above but for answers

		currentQuestionIndex = r; //saving the current index -> e.g. the just drawn random int


	}
	else { //if the two vectors are not of the same size, the game will exit
		cout << "Error: There aren't as many questions as answers \nin the vectors: questions & answers" << endl;
		exit(EXIT_FAILURE);
	}

}

void Vocabulary::loadVocabularyFile() {//opening the vocabulary file
	std::ifstream ip(fName); //opening the file using the name stored in fName

	if (!ip.is_open()) { // if the file is not opened -> print warning and exit
		cout << "ERROR: File Open" << endl;
		exit(EXIT_FAILURE);
	}
	std::string q;
	std::string a;

	while (ip.good()) { //if file openend successfully
		std::getline(ip, q, ','); //get everything on the same line until "," and read it into q
		std::getline(ip, a, '\n'); //same as above: read everything after "," and before the newline delimiter into a
		questions.push_back(q); //add q to questions
		answers.push_back(a); // add a to answers
	}

	ip.close(); //close file
	vocabularyLoaded = true; //set vocabularyLoaded to true
}

int Vocabulary::randomInt(int start, int end) { // return random integer between start and end.
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(start, end);
	return distr(eng);
}

bool Vocabulary::isInVector(std::vector<int> v, int i) { //check if a given integer is present in vector and return bool based on that
	if (std::find(v.begin(), v.end(), i) != v.end()) {
		return true;
	}
	else {
		return false;
	}
}

void Vocabulary::addAskedQuestion(int i) { //adds integer i to askedQuestions
	askedQuestions.push_back(i);
}

// one-line getters -> self explanatory

std::string Vocabulary::returnCurrentQuestion() { return currentQuestion; }

std::string Vocabulary::returnCurrentAnswer() { return currentAnswer; }

std::string Vocabulary::accessQuestionViaIndex(int i) { return questions[i]; }

std::string Vocabulary::accessAnswerViaIndex(int i) { return answers[i]; }

int Vocabulary::returnQuestionIndex() { return currentQuestionIndex; }

std::vector<int> Vocabulary::getAskedQuestions() { return askedQuestions; }
