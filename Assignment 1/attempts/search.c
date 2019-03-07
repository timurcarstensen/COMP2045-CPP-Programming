// 20178811 biytc4 Timur Michael Carstensen

#include <stdio.h>
#include <string.h>

#define MAXCHAR 10000

int countSubstring(const char *m, const char *s)
    {
        int l = strlen(s);
        if (l == 0) return 0;
        int count = 0;
        for (m = strstr(m, s); m; m = strstr(m + l, s))
            ++count;
        return count;
    }

int main(int argc, char* argv[])
{

    char *fileName;

    if ( argc != 2 )
    {
        printf("Invalid command line arguments. Usage: ./search textfile\n");
    }
    else if ( argc == 2)
    {
        fileName = argv[1];
        // printf("%s\n", fileName);


    FILE *fp; // opening the file


    char str[MAXCHAR];

    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Cannot open file\n %s",fileName);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        // printf("%s", str);
    fclose(fp);


    char searchString[20];
    printf("Search for: ");
    scanf("%[^\n]%*c", searchString);

    // printf("%s\n", searchString );

    int count = countSubstring(str, searchString);

    if (count == 1)
        {
            printf("%d occurance found in the file\n", count);
        }
    else if (count > 1 || count == 0)
        {
            printf("%d orccurances found in the file\n", count);
        }


    return 0;


    }
}



