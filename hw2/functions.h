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

#include <stdio.h>  // printf, scanf, sprintf
#include <stdlib.h> //  srand, rand
#include <time.h> // time
#include <string.h> // strcpy, strcat
#include <dirent.h> // directory stuff
#include <sys/stat.h>
#include <fcntl.h> // open
#include <unistd.h> // close

struct movies {
  char *title;
  int year;
  char **langs;
  int n_langs;
  float rating;
};

// main loop
void userOptions(int *);
void checkOptions(int, int *);
void selectFileProcess();
void checkSelectFile(int);

// processing files
void processLargest();
void processSmallest();
void processFilename();
char *findLargest();
char *findSmallest();
char *createFoldername();

// helpful functions
void clearInput();

#endif
