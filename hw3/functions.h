#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// main loop and operations
void smallsh_loop();
char *smallsh_getInput();
char **smallsh_splitInput(char *);
int smallsh_execute();

#endif
