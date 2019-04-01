// 20178811 biytc4 Timur Michael Carstensen
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

class TextFileObject {
    
    public: 
    string data; 

    TextFileObject(string f) { //default constructor
        // cout << "constructor has been called" << endl;
        if (checkIfFileIsAccessible(f)) { 
            fileName = f;                 
            openFile(fileName);           
        } else if (!checkIfFileIsAccessible(f)) { 
            cout << "Cannot open file" << endl;
            exit (EXIT_FAILURE);
        }
    }

    ~TextFileObject() { //default destructor
        // cout << "destructor has been called" << endl;
    }; 

    void setInput(string i) {
        input = i;
    }

    string findMostSimilarString() {
        int count = 0;
        int times = 0;
        string similarString = "";
        string tempString = ""; 
    
        for (int i = 0; i <= data.length() - input.length(); i++) {
            int j;
            times = 0;
            tempString = "";
            
            for (j = 0; j < input.length(); j++) {

                if (data[i+j] == input[j]) {
                    times++;
                }
                    tempString += data[i+j];
            }

            if (times > count) {
                count = times;
                similarString = tempString;
            }
        }
    return similarString;
    }

    private:
    string input;
    string fileName; 
    string word; 

    void openFile(string f) {
        fstream file;
        file.open(f);
        while (file >> word) {

            data += word + " "; 
        }
        file.close();
    }

    bool checkIfFileIsAccessible(string f) {
        struct stat buffer;   
        return (stat (f.c_str(), &buffer) == 0); 
    }   

};

int findString(string input, string file) {
    int occurrences;
    if(input.find_first_not_of(' ') != string::npos) {
        
        size_t size = 0;

        while ((size = file.find(input, size)) != string::npos) {
            ++occurrences;
            size += input.length();
        }
        if (occurrences == 0) {
            cout << occurrences << " occurences found in this file. ";
        } else if (occurrences == 1) {
            cout << occurrences << " occurence found in this file" << endl;
        } else if (occurrences > 1) {
            cout << occurrences << " occurences found in this file" << endl;
        }
        return occurrences;
    }
    return 1;
}


int main(int argc, char *argv[]) {
   
    if (argc < 2) {
      cerr << "Invalid command line arguments. Usage: ./fuzzysearch textfile" << endl;
      exit(1);
    }

    TextFileObject obj1(argv[1]); 

    string input = " ";
    
    while(!input.empty()) {
    
        cout << "Please enter the string to be searched for: ";
        getline(cin, input);

        int i = findString(input, obj1.data);
    
        if (i == 0) {
            obj1.setInput(input);
            cout << "Most similar string: " << obj1.findMostSimilarString() << endl;
        }
    }
    return 0;
}

