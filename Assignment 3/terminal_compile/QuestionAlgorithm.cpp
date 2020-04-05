#include "QuestionAlgorithm.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

QuestionAlgorithm::QuestionAlgorithm(std::string n) { //constructor call with string argument
    setPlayerName(n); //call setPlayerName with argument n
    loadCfg(); //calling loadCfg()
}

void QuestionAlgorithm::addResultToCfgElement(int index, float performance) {
    if (performance < 1) {  //adds result to the config unless the player answered the question completly correct.
        std::string i = std::to_string(index); //question index as string
        std::string p = std::to_string(performance); //adding performance as string
        cfgElement += i + ", " + p + "; "; //using string concatenation
    }
}

void QuestionAlgorithm::writeToConfig() {
    std::ofstream outfile; //initialising ofstream
    outfile.open("player_config.csv", std::ios_base::app); //opening config file in mode "append"
    
    if (hasConfig()) { //if the player has a config then do the following:
        //deleting old config and closing file
        delete_line(fileName.c_str(), lineNoPlayerName);
        delete_line(fileName.c_str(), lineNoPlayerName);
        outfile.close();
        
        //re-opening file and appending new config
        outfile.open("player_config.csv", std::ios_base::app);
        outfile << playerName << endl;
        outfile << returnCfgElement() + "\n";

        outfile.close();
    
    } else if (!hasConfig()) {

        //player has no config --> appending new config and closing file
        outfile << playerName << endl;
        outfile << returnCfgElement() + "\n";
        outfile.close();
    }
}

bool QuestionAlgorithm::isNewPlayer() {
    if (lineNoPlayerName) { return false; } //if there is a line number for the player name the function will return false and exit the function scope -> e.g the player is not "new"
    return true; //else the function will return true, indicating that the player hasn't played the game before
}

bool QuestionAlgorithm::hasConfig() {
    if (!isNewPlayer()) {
        //if the player is not new..
    } else if (isNewPlayer()) {
//      if the player is new the function will return false, indicating that the player does not have a config
        return false;
    }
    
    if (cfgLine.empty()) {
        //if the cfgLine attribute is empty, the function returns false -> e.g. the player does not have a config
        return false;
    } else { //else return true -> the player has a config
        return true;
    }
}

int QuestionAlgorithm::returnRandomQuestion() { //returns a random question from the config
   
    /*
     it selects a random question from one vectors (b1 to b4), returns that question
     and deletes the question that has just been returned using
     returnRandomDelete(). This ensures that the same question won't be asked twice.
     */
    if (!b1.empty()) {

        setCurrentQuestionIndex(returnRandomDelete(b1));
        return returnCurrentQuestionIndex();
        
    } else if (!b2.empty()) {

        setCurrentQuestionIndex(returnRandomDelete(b2));
        return returnCurrentQuestionIndex();
        
    } else if (!b3.empty()) {

        setCurrentQuestionIndex(returnRandomDelete(b3));
        
        return returnCurrentQuestionIndex();
        
    } else if (!b4.empty()) {

        setCurrentQuestionIndex(returnRandomDelete(b4));
        
        return returnCurrentQuestionIndex();
        
    } else { //if none of the vectors above satisfy the if conditions the function will return 10000. This will be used in main() to determine if there are any more questions stores in the config. If 10000 is returned the main() function will use control flow to call a random question from the Vocabulary class
        
        return 10000;
    }
}

void QuestionAlgorithm::segmentCfg() { //this function segments the "index, performance" pairs stored in the config.
    
    vector<std::string> v = tmpVector;
    
    /*
        The following for loop iterates over all the items in vector v (which is equal to vector tmpVector).
        Previously, the splitCfg() function has populated the vector tmpVector.
        It populated the vector with "tuples" of "index, performance;" pairs.
     Now these pairs will be further split up. The performance value will be used
     to determine in which bracket correlating index should be sorted
    */
    
    for (vector<std::string>::iterator t=v.begin(); t!=v.end(); ++t) { //iterating over v
        // variables
        std::stringstream f(*t); //creating strinstream from t
        std::string s;
        
        int currentIndex, i = 0;
        float currentFloat = 0;
        
        while(std::getline(f, s, ',')) { // splitting on ","
            ++i;
            s = std::regex_replace(s, std::regex("^ +"), ""); //remove leading whitespace
            
            if (i == 1) { //if i is 1 -> currentIndex equal to integer of s
                currentIndex = std::stoi(s);
            } else if (i == 2) { //if i is 2 -> currentFloat equal to float of s
                currentFloat = std::stof(s);
            }
        }
        
        if (currentFloat != 0) { //this control flow section segments the index into the correct bracket based on its value. The value represents the percentage the user answered correctly or rather how closely the user's answer matched the actual correct answer
            if (currentFloat <= 0.25) {
                
                b1.push_back(currentIndex);
                
            } else if (0.26 <= currentFloat && currentFloat <= 0.5) {
                
                b2.push_back(currentIndex);
                
            } else if (0.51 <= currentFloat && currentFloat <= 0.75) {
                
                b3.push_back(currentIndex);
                
            } else if (0.76 <= currentFloat && currentFloat <= 1) {
                
                b4.push_back(currentIndex);
            }
        }
    }
}

void QuestionAlgorithm::loadCfg() { //loads config from file
    int cLine = 0; //current line
    
    std::string line;
    std::ifstream f1(fileName);
    std::ifstream f2(fileName);
    
    if (!f1.is_open()) { //checks if f1 is open -> if not, the program will terminate
        cout << "ERROR! File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }
    int i = returnConfigLine(f1); //getting the line number of the config line
    
    
    while (getline(f2, line)) { //reading into line from f2
        ++cLine; //incrementing cLine
        if (cLine == i) { //if "cLine" equals int "i" -> we have found the line in which the config is stored
            
            cfgLine = line; //that line is saved back to the attribute cfgLine
            splitCfg(); //calling splitCfg();
            segmentCfg(); //calling segmentCfg();
        }
    }
    
    f1.close(); //closing files
    f2.close();

}

void QuestionAlgorithm::splitCfg() { //splits the config line on ";" to seperate it into the vector tmpVector
    std::stringstream f(cfgLine);
    std::string s;
    
    while(std::getline(f, s, ';')) {
        s = std::regex_replace(s, std::regex("^ +"), ""); //remove leading whitespace
        tmpVector.push_back(s);
    }
}

int QuestionAlgorithm::returnConfigLine(std::ifstream &f) { // getting configuration's line no
    std::string line;
    int a = 0, b = 0;
    while (getline(f, line)) {
        ++a;
        if (line == playerName) { //finds the line on which the player's name is located
            lineNoPlayerName = a;
            b = (a + 1); //takes player name line number and adds 1 to find the line on which the configuration is stored
        }
    }
	
    return b;
}

int QuestionAlgorithm::returnRandomDelete(vector<int> v) {
    int i = randomInt(0, int(v.size()-1)); //using randomInt from the Vocabulary class
    int tmp = v[i]; //accessing the passed in vector with int "i"
    try {
		v.erase(v.begin() + (i - 1)); //deleting the just passed in value
	} catch (...) {
		//do nothing
	}
    return tmp;
}

void QuestionAlgorithm::delete_line(const char *file_name, int n) {
    std::ifstream input(file_name); //opening original file

    std::ofstream output; //creating & opening file in write mode
    output.open("tmp.csv", std::ofstream::out);
    
    char chr;
    int lineNo = 1;
    while (input.get(chr)) { //while lopp getting all characters
    
        if (chr == '\n') { // if newline -> increment lineNo
            lineNo++;
        }
    
        if (lineNo != n) { // content that should not be deleted --> if lineNo not equal to "n", "chr" will be written to output.
            output << chr;
        }
    }
    
    output.close(); //closing both files
    input.close();
    
    remove(file_name); // removing the original file
    rename("tmp.csv", file_name); // renaming the temp file to the original file name
}

//single line setters

void QuestionAlgorithm::setPlayerName(std::string n) { playerName = n; }

//single line return statements

std::string QuestionAlgorithm::returnCfgElement() { return cfgElement; }

std::string QuestionAlgorithm::returnCfg() { return cfgLine; }

int QuestionAlgorithm::returnCurrentQuestionIndex() { return currentQuestionIndex; }

void QuestionAlgorithm::setCurrentQuestionIndex(int i) { currentQuestionIndex = i; }
