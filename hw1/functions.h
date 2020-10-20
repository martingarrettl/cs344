/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 28/9/2020
  Class: CS344
  Section: 001
  Assignment: 1 - Movies
***************************************************************************/

#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct film {
  char *title;
  int year;
  char **languages;
  int nLang; // # of languages in array, not size of array
  float rating;
  struct film *next; // hey look at me im a linked list
};

// main program operations
void printOptions(struct film *, int *);
void checkOption(int opt, struct film *f, int *end);
void moviesByYear(struct film *f);
void highestRated(struct film *f);
void moviesByLanguage(struct film *f);
int compareYears(struct film *dest, struct film *source);

// functions used to build and free the linked list
struct film *copyFilm(struct film *source);
struct film *extractData(char *filename);
struct film *newNode(char *source);
void copyPush(struct film *dest, struct film *source);
char **getLanguages(char *, int *);
void freeFilms(struct film *);
void freeNoString(struct film *);

// prints used for debugging
void printFilms(struct film *films);
void printFilm(struct film *f);

// specific task helpers
int listSize(struct film *);
void clearInput();

#endif
