/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 21/10/2020
  Class: CS344
  Section: 001
  Assignment: 3 - smallsh
  Description:
***************************************************************************/

#include "functions.h"

/**************************************************************************
  Title: smallsh_loop
  Description: main loop for small shell application.
***************************************************************************/
void smallsh_loop() {
  char *input;
  char **args;
  int status = 1;

  while (status == 1) {
    printf("> : ");
    input = smallsh_getInput();
    args = smallsh_splitInput(input);
    status = smallsh_execute();

    free(input);
    free(args);
  }
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
char *smallsh_getInput(){

  // modify this to max 2048 char limit
  char *input = NULL;
  size_t len = 0;
  ssize_t read = getline(&input, &len, stdin);

  // length limit of 2048 characters
  if (len > 2048) {
    perror("Exceeded command line length input");
    exit(EXIT_FAILURE);
  }

  // check read failures. EOF causes successful exit.
  if (read == -1) {
    if(feof(stdin)) {
      exit(EXIT_SUCCESS);
    } else {
      perror("Read Failure");
      exit(EXIT_FAILURE);
    }
  }

  return input;
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
char **smallsh_splitInput(char *input){
  // max of 512 args
  char **args = (char **)calloc(512, sizeof(char *));

  char *temp = NULL;
  char *token = strtok_r(input, " ", &temp);


  return args;
}
