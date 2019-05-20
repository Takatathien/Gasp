// Thien Trinh
// Homework 5
// Problem 1
// 05/01/19

/*
 This program performed similar to grep, where the user can input a search string and a file, which it will then print out the lines containing the search string inside the file onto stdout. 
 There are two options, -n which displace the line number, and -i which match the search string with the line, regardless of case.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Control the max lines inside the input file.
#define MAX_LINE 500
// Control the max length of the input string.
#define MAX_LENGTH 100

// Counter to check if the options if flagged(1) or not(0)
int hasI;
int hasN;

int grep(char *argv[], int i);
int matchStr(char *fileLine, char* targetLine);

/*
 The main method to check if the arguments given are less than 3, and given appropriate error.
 If the arguments given are 3 or more, then check the options given to tag it and send all the arguments to the grep function.
 */
int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Less than 3 arguments: %i\n", argc);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (argv[i][1] == 'i') {
      hasI = 1;
    } else if (argv[i][1] == 'n') {
      hasN = 1;
    } else {
      fprintf(stderr, "Invalid option: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
  }

  for (int i = hasI + hasN + 2; i < argc; i++) {
    grep(argv, i);
  }

  return EXIT_SUCCESS;
}

/*
 Get the file from the arguments and check if it exist.
 If hasI is tagged, then send all the arguments the matchStr function.
 If not then just check to see if there is a match.
 If there is a match, then check if hasN is tagged, and print the appropriate responds to stdout.
 */
int grep(char *argv[], int input) {
  FILE *file = fopen(argv[input], "r");
  if (file == NULL) {
    fprintf(stderr, "Does not exist: %s\n", argv[input]);
    exit(EXIT_FAILURE);
  }

  char fileLine[MAX_LINE];
  int lineCount = 0;
  while (fgets(fileLine, MAX_LINE, file)) {
    lineCount++;
    int matchLowerCase = 0;
    char *match = NULL;
    if (hasI == 1) {
      matchLowerCase = matchStr(fileLine, argv[hasI + hasN + 1]);
      if (matchLowerCase == -1) {
        fprintf(stderr, "Input string over limit");
        exit(EXIT_FAILURE);
      }
    } else {
      match = strstr(fileLine, argv[hasI + hasN + 1]);
    }

    if (matchLowerCase > 0 || match != NULL) {
      if (hasN == 1) {
        printf("%s:%i:%s", argv[input], lineCount, fileLine);
      } else {
        printf("%s:%s", argv[input], fileLine);
      }
    }
  }

  fclose(file);
  return 0;
}

/*
 Convert both the input string and the file line to lower case.
 Match them and return
 */
int matchStr(char *fileLine, char *targetLine) {
  int len1 = strlen(fileLine);
  int len2 = strlen(targetLine);

  if (len2 > MAX_LENGTH) {
    return -1;
  }

  char *str1 = (char*) malloc(len1 * sizeof(char));
  char *str2 = (char*) malloc(len2 * sizeof(char));

  for (int i = 0; i < len1; i++) {
    str1[i] = tolower(fileLine[i]);
  }
  for (int i = 0; i < len2; i++) {
    str2[i] = tolower(targetLine[i]);
  }

  int match = 0;
  if (strstr(str1, str2)) {
    match = 1;
  }

  free(str1);
  free(str2);
  return match;
}
