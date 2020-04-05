//importing all necessary files
#include "Timer.hpp"
#include "Vocabulary.hpp"
#include "Game.hpp"
#include "InputCompare.hpp"
#include "QuestionAlgorithm.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char* argv[]) {
	Game game = Game(argc, argv); //initialising all objects necessary in the main() function
	Vocabulary v;
	InputCompare ic;
	QuestionAlgorithm qa = QuestionAlgorithm(game.getPlayerName());
	Timer t1, t2;
	Timer* t2ptr = &t2;

	std::vector<int> askedQuestions; //vector of integers to store all asked question in this game -> will be used later in main() to ensure, that the user won't have to answer the same question twice

	game.presentWelcomeMessage(); // present the user with a personalized welcome message

	game.delayBy(1.5, t2ptr, true); //delay game by 1.5 seconds and clear screeen


	while (true) {
		std::string in;
		cout << "would you like to start the game?\nPlease type in y (for yes) to start\nor n (for no) to end the program!" << endl;
		getline(cin, in);
		if (in == "y") {

			break;
		}
		else {
			cout << "Goodbye!" << endl;
			return 0;
		}
	}

	game.delayBy(1, t2ptr, true); //delay game by 1 second and clear screeen


	while (game.getCurrentRound() < game.getGameRounds()) { //while loop that runs as long as the current round count is  less than the total specifiec rounds by the user
		cout << "NEW ROUND \n" << endl;
		game.incrementRoundCount(); //incrementing the round count
		int q = qa.returnRandomQuestion(); //returning a random question from the config
		int counter = 0;

		while (v.isInVector(askedQuestions, q)) { //running while loop until a random question is returned that has not been previously asked in this game
			q = qa.returnRandomQuestion();
			++counter;
			if (counter > 40) { //this is needed when running this program with Visual Studio. On macOS it ran completly fine without this
				q = 10000;
				break;
			}
		}


		std::string usrIn; //setting string for user input

		/*
		 if q > 1000 -> there are no more questions in the config that havent been asked before
		 therefore, the game will now use the Vocabulary class and the returnRandomQuestionFromVocabulary() method
		 to ask the user new questions
		 */

		if (q > 1000) {
			v.returnRandomQuestionFromVocabulary();
			int i = v.returnQuestionIndex();

			while (v.isInVector(askedQuestions, i)) { //same as before -> reassigns int "i" until it is not found in the previously asked questions to ensure that the user will not get asked the same question twice
				v.returnRandomQuestionFromVocabulary();
				i = v.returnQuestionIndex();
			}
			q = i; //when we have ensured, that "i" has not been asked before, "q" is assigned "i"

		}

		cout << v.accessQuestionViaIndex(q) << endl; //printing out question to the usr

		cout << "please input your answer" << endl;

		t1.start(); //starting timer



		getline(cin, usrIn); // getting user input


		if (t1.elapsedSecs() > game.getGameTime()) { //checking if the user has input the answer in the specified timeframe that was defined by the user in the command line arguments
			cout << "you ran out of time" << endl;
			ic.setInput(""); //if the user ran out of time, the answer will be set to an empty string -> this leads to the user getting a 0% rating for that question -> so this question will definitely be one of the first ones to be asked when the user plays the game the next time
			t1.stop();
		}
		else { //if the user input the answer in due time, the input will be set to his answer
			ic.setInput(usrIn); //setting the answer in the InputComare class object "ic"
			t1.stop();
		}



		ic.setAnswer(v.accessAnswerViaIndex(q)); //setting the correct answer in the InputCompare class object "ic"

		/*
		Adding the result of the current round to the cfgElement which will be then later
		 written to the config file. "q", being the index of the question, will be written, as well as
		 the performance result in the form if a double which is returned by ic.fuzzyComparison().
		*/
		qa.addResultToCfgElement(q, ic.fuzzyComparison());

		askedQuestions.push_back(q); //finally, the current round's question index is added to askedQuestions so that the user will not have to answer the same question twice
	}



	qa.writeToConfig(); //after all the rounds have been played, the cfgLine attribute as well as the player name are written to the config file

	cout << "game has finished" << endl;




}
