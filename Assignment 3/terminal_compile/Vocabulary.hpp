#ifndef Vocabulary_hpp
#define Vocabulary_hpp

#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;



class Vocabulary {
    
public:
    Vocabulary();
    
    //getters
    std::vector<int> getAskedQuestions();
    void returnRandomQuestionFromVocabulary();
    int randomInt(int start, int end);
    int returnQuestionIndex();
    std::string returnCurrentQuestion();
    std::string returnCurrentAnswer();
    std::string accessQuestionViaIndex(int i);
    std::string accessAnswerViaIndex(int i);
    
    bool isInVector(std::vector<int> v, int i);
    void addAskedQuestion(int i);
    void loadVocabularyFile();
    
private:
    
    //integers
    int currentVocabulary;
    int currentQuestionIndex;
    
    //strings
    std::string currentQuestion;
    std::string currentAnswer;
    std::string fName = "vocabulary.csv";
    
    //vectors
    std::vector<std::string> questions;
    std::vector<std::string> answers;
    std::vector<std::string> fileNames;
    std::vector<int> askedQuestions;
    
    //booleans
    bool vocabularyLoaded = false;
};

#endif /* Vocabulary_hpp */
