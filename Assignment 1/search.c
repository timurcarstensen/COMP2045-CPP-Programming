/* 20178811 biytc4 Timur Michael Carstensen
NOTE:
    I haven't had the chance to test this on the linux server in the lab. However, my code does compile and run when using the terminal in macOS with the following command: "gcc -std=c99 -lm -Wall -Wformat -Wwrite-strings search.c -o search"

ALSO:
    I was not able to remove the restriction for user input regarding input size. Therefore, I have set the buffer size to 512 which should be plenty for any kind of input
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int findKeyWord(char *in, char *key, int b) { //function takes in a filename, a "key" to be searched for and a buffer that has to be predefined
    int total = 0;
    FILE *f;
    f = fopen(in,"r"); //opening the text file in read more (r)
    char t[b];
    while(fgets(t, b , f) != NULL){
        char *p = t;
        while((p=(strstr(p, key)))!= NULL){ //compares strings with strstr
            total++; // increments total by 1
            ++p;
        }
    }
    fclose(f); //closes file
    return total; //returns total occurences
}


int main(int argc, char* argv[]){
    char *f;

    if (argc != 2) { //checking for correct user command line input
        printf("Invalid command line arguments. Usage: ./search textfile\n");
    } else if (argc == 2) {
        f = argv[1]; //setting the file name "f" equal to the command line input
        if (access(f, F_OK) != -1) { //now that we know that the user command line input is "correct" we have to check if the file exists

        } else {
            printf("Cannot open file\n"); //if the file doesn't exist we print an error message
            exit(0);
        }

        int wordCount = 0;
        char s[512]; //setting the buffer to 512 to accomodate for larger user input
        int r;

        while(1) {
            printf("Search for: ");
            r = scanf("%[^\n]%*c", s); //getting user input
            if (r == 0) { //if user input is empty --> terminate the program
                break;
            } else { //if user input is not empty --> call function to count occurences of user input in text file
                wordCount = findKeyWord(f, s, 512); //setting the buffer
                printf("%d occurance found in the file\n", wordCount); //printing total occurences of user input string
            }
        }
    }
    return 0;
}
