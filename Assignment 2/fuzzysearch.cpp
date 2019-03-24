#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()
 
int main(int argc, char* argv[])
{
    using namespace std;

    if (argc < 2) 
    {
      cerr << "Invalid command line arguments. Usage: ./fuzzysearch textfile" << endl;
      exit(1);
    };  

    ifstream inf(argv[1]); // ifstream is used for reading files // We'll read from a file called Sample.dat

    if (!inf) // If we couldn't open the input file stream for reading
    {
        cerr << "Cannot open file" << endl; // Print an error and exit
        exit(1);
    }
    
    while (inf) // While there's still stuff left to read
    {
        std::string strInput; // read stuff from the file into a string and print it
        getline(inf, strInput);
        cout << strInput << endl;
    }
    // When inf goes out of scope, the ifstream
    // destructor will close the file
}