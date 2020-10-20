/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 18/10/2020
  Class: CS344
  Section: 001
  Assignment: 2 - Files & Directories
***************************************************************************/

#include "functions.h"

int main() {
  int end = 0;
  srand(time(0));

  // main program loop
  while (end == 0) {
    userOptions(&end);
  }

  return EXIT_SUCCESS;
}
