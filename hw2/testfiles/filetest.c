#include <stdio.h>  // printf, scanf, sprintf
#include <stdlib.h> //  srand, rand
#include <time.h> // time
#include <string.h> // strcpy, strcat, strncmp, strstr
#include <dirent.h> // directory stuff
#include <sys/stat.h> // stat struct
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

struct years {
  char *year;
  struct years *next;
};

struct years *newNode(char *source) {
  char *temp;
  char *token = strtok_r(source, ",", &temp);
  token = strtok_r(NULL, ",", &temp);

  char *year = (char *)calloc(1, sizeof(token) + 1);
  strcpy(year, token);
  strcat(year, "\0");

  struct years *node = (struct years *)calloc(1, sizeof(struct years));
  node->year = year;
  node->next = NULL;

  return node;
}

struct years *getYears(char *filename) {

  FILE *data = fopen(filename, "r");
  char *temp = NULL;
  size_t len = 0;
  ssize_t nread;
  struct years *head = NULL;

  while ((nread = getline(&temp, &len, data)) != -1) {
    char *temp2;
    char *token = strtok_r(temp, ",", &temp2);
    token = strtok_r(NULL, ",", &temp2);

    if (head == NULL) {
      struct years *node = newNode(temp);
      head = node;
    } else {
      int newyear = 0;
      struct years *nav = head;
      while (nav != NULL) {
        if (strcmp(token, nav->year) != 0) {
          newyear = 1;
        }
        nav = nav->next;
      }
      if (newyear == 1) {
        nav = head;
        while (nav->next != NULL) {
          nav = nav->next;
        }
        nav->next = newNode(temp);
      }
    }
  }

  return head;
}

int main(void){
	char newFilePath [] = "movies_sample_1.csv";
  struct years *y = getYears(newFilePath);
  struct years *nav = y;

  int i = 1;
  while (nav != NULL) {
    printf("%d: %s\n", i, nav->year);
    ++i;
  }

  while (y != NULL) {
    struct years *temp = y;
    y = y->next;
    free(temp->year);
    free(temp);
  }

	return 0;
}
