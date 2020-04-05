#ifndef InputCompare_hpp
#define InputCompare_hpp


#include <iostream>
#include <regex>


using std::cin;
using std::cout;
using std::endl;
using std::vector;

class InputCompare {
public:
    
    //functions
    int determineHealthPointsToLoose(float p);
    float fuzzyComparison();
    
    void setAnswer(std::string n);
    void setInput(std::string n);
    
private:
    //strings
    std::string answer;
    std::string userInput;
    
    //pointers
    std::string *answerptr = &answer;
    std::string *userInputptr = &userInput;
    
    //numbers
    int maxScore;
    float scorePercentage;
    
    //functions
    std::string toLower(std::string str);
    std::string removeWhitespace(std::string str);
    void addSpaces(std::string *original, std::string *in);
};


#endif /* InputCompare_hpp */
