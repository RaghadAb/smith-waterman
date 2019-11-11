#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Smith-Waterman.h"

// method to get a and b
void getStrings(char *line, char a[], char b[])
{
    // get a first
    int i = 0;

    // as long as there is whitespace
    while (i < strlen(line) && isspace(line[i]))
    {
        i++;
    }

    // the index of a
    int index = 0;
    // accumulate a
    while (i < strlen(line) && !isspace(line[i]) && line[i] != ',')
        a[index++] = line[i++];
    a[index] = '\0';

    // get b
    // move forward as long as space
    i++;
    while (i < strlen(line) && isspace(line[i]))
        i++;
    index = 0;
    // accumulate b
    while (i < strlen(line) && !isspace(line[i]))
        b[index++] = line[i++];
    b[index] = '\0';
}

int main(int argc, char **argv)
{
    // check for the right number of command line arguments
    if (argc != 2)
    {
        // show usage
        printf("Usage : %s <csv_file_name>\n", argv[0]);
        // stop running
        return 0;
    }
    // first command line argument (stored in argv[1]) is the csv filename
    // open the csv file
    FILE *fp = fopen(argv[1], "r");
    // load in csv line-by-line (ignoring lines starting by #;
    //                           you can assume that a line will be never
    //                           longer than 256 characters)

    // if cannot open file, show message
    if (!fp)
    {
        // show message cannot open file
        printf("Cannot open file : %s\n", argv[1]);
        return 0;
    }

    // the strings a and b
    char *a = (char *)malloc(sizeof(char) * 257);
    char *b = (char *)malloc(sizeof(char) * 257);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // get a and b
        // get the length of the line
        int lineLength = strlen(line);
        // set this to null terminator
        line[lineLength - 1] = '\0';
        // get a and b
        getStrings(line, a, b);

        // print a and b
        // printf("a : %s\n",a);
        // printf("b : %s\n",b);

        print_smith_waterman(a, b);
    }
    fclose(fp);
    // for each line:
    //   read string up to `,' as the first string
    //   read string after `,' up to the newline character as the second string
    //   remove whitespace at the start and end of each string
    //   call `print_smith_waterman' with the first and second string
    // close the csv file

    //
    // print_smith_waterman("GGTTGACTA", "TGTTACGG");

    return EXIT_SUCCESS;
}
