/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 28/9/2020
  Class: CS344
  Section: 001
  Assignment: 1 - Movies
***************************************************************************/

#include "functions.h"

int main( int argc, char *argv[] ) {
  // require a filename to be provided as argument
  if (argc < 2) {
    printf("Filename required as argument.\n");
    printf("Ex: ./movies bestfilmz.csv\n");
    return EXIT_FAILURE;
  }

  struct film *films = extractData(argv[1]);

  // main program loop
  int end = 0;
  while (end == 0) {
    printOptions(films, &end);
  }

  freeFilms(films);
  return EXIT_SUCCESS;
}
