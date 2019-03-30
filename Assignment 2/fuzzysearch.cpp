#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()

int findString(std::string in, std::string text) {
    using namespace std;
    int occurrences;
    string::size_type pos = 0;
    while ((pos = text.find(in, pos)) != std::string::npos) {
          ++ occurrences;
          pos += in.length();
    }
    cout << occurrences << " occurences found in this file"<<endl;
    return 0;
}

 
int main(int argc, char* argv[])
{
    using namespace std;

    if (argc < 2) 
    {
      cerr << "Invalid command line arguments. Usage: ./fuzzysearch textfile" << endl;
      exit(1);
    }; 

    ifstream ifs(argv[1]);
    string content( (istreambuf_iterator<char>(ifs) ),
                       (istreambuf_iterator<char>()    ) );

    string subString;

    while(true) {
    cout << "Please enter the string to be searched for: ";
    string input;
    getline(cin, input);

    if (!input.empty()) {
        findString(input, content);
        subString = input;
    } else {
        break;
    }
    }


    

}




















//     if (argc < 2) 
//     {
//       cerr << "Invalid command line arguments. Usage: ./fuzzysearch textfile" << endl;
//       exit(1);
//     };  

//     ifstream inf(argv[1]); // ifstream is used for reading files // We'll read from a file called Sample.dat


//     if (!inf) // If we couldn't open the input file stream for reading
//     {
//         cerr << "Cannot open file" << endl; // Print an error and exit
//         exit(1);
//     }
    
//     std::string fileText;
    
//     while (inf) // While there's still stuff left to read
//     {
//         std::string strInput;    
//         getline(inf, strInput);
//         cout << strInput << endl;
//         fileText += strInput;
//     }
    
//     cout << fileText << endl;
//     // When inf goes out of scope, the ifstream
//     // destructor will close the file
// }