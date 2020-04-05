#ifndef QuestionAlgorithm_hpp
#define QuestionAlgorithm_hpp

#include <sstream>
#include <regex>
#include "Vocabulary.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class QuestionAlgorithm : public Vocabulary {

public:

	// set-up functions & constructor

	QuestionAlgorithm(std::string n);

	void loadCfg();

	void addResultToCfgElement(int index, float performance);

	// getters
	int returnRandomQuestion();

	int returnCurrentQuestionIndex();


	// setters

	void setPlayerName(std::string n);

	void writeToConfig();

	std::string returnCfg();

	std::string returnCfgElement();


private:

	// integers
	int lineCount;
	int lineNoPlayerName;
	int sizeOfCurrentBracket;
	int currentQuestionIndex;

	// strings
	std::string cfgLine;
	const std::string fileName = "player_config.csv";
	std::string playerName;
	std::string cfgElement;

	// vectors
	vector<std::string> tmpVector;
	vector<int> b1; // 0 - 25 %
	vector<int> b2; // 26 - 50 %
	vector<int> b3; // 51 - 75 %
	vector<int> b4; // 76 - 100  %

	bool newPlayer;





	/*          ALL PRIVATE FUNCTIONS             */

		// bools
	bool isNewPlayer();
	bool hasConfig();

	//getters

	int returnRandomDelete(vector<int> v);

	void segmentCfg();

	void splitCfg();

	int returnConfigLine(std::ifstream& f);

	void setCurrentQuestionIndex(int i);

	void delete_line(const char* file_name, int n);

	// pointers

	vector<int>* b1pt = &b1;
	vector<int>* b2pt = &b2;
	vector<int>* b3pt = &b3;
	vector<int>* b4pt = &b4;

};

#endif /* QuestionAlgorithm_hpp */
