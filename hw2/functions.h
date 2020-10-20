/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 18/10/2020
  Class: CS344
  Section: 001
  Assignment: 2 - Files & Directories
***************************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define PREFIX "movies_"
#define SUFFIX ".csv"

#include <stdio.h>  // printf, scanf, sprintf
#include <stdlib.h> //  srand, rand
#include <time.h> // time
#include <string.h> // strcpy, strcat, strncmp, strstr
#include <dirent.h> // directory stuff
#include <sys/stat.h> // stat struct
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

// main loop
void userOptions(int *);
void checkOptions(int, int *);
void selectFileProcess();
void checkSelectFile(int);

// related to largest/smallest/specified filename
void processLargest();
void processSmallest();
void processFilename();
char *findLargest();
char *findSmallest();
int findFilename(char *);
char *createFoldername();

// process the csv
void processCSV(char *, char *);

// helpful functions
void clearInput();

#endif
