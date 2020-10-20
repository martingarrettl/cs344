/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 28/9/2020
  Class: CS344
  Section: 001
  Assignment: 1 - Movies
***************************************************************************/

#include "functions.h"

/**************************************************************************
  Title: printOptions
  Description: prints the set of functions available to the user
***************************************************************************/
void printOptions(struct film *f, int *end) {
  int option;

  printf("1. Show movies released in specified year\n");
  printf("2. Show highest rated movie for each year\n");
  printf("3. Show the title and year of release of all movies in a specified language\n");
  printf("4. Exit\n\n");
  printf("Choose an option (1-4): ");
  scanf("%d", &option);
  checkOption(option, f, end);
}

/**************************************************************************
  Title: checkOption
  Description: Handles the user input from printOptions.
***************************************************************************/
void checkOption(int opt, struct film *f, int *end) {
  switch(opt) {
    case 1:
      moviesByYear(f);
      printOptions(f, end);
      break;
    case 2 :
      highestRated(f);
      printOptions(f, end);
      break;
    case 3 :
      moviesByLanguage(f);
      printOptions(f, end);
      break;
    case 4 :
      *end = 1;
      break;
    default :
      printf("Invalid input, please try again\n");
      printOptions(f, end);
  }
}

/**************************************************************************
  Title: moviesByYear
  Description: prints all movies from a specified year
***************************************************************************/
void moviesByYear(struct film *f){
  int y, printednothing = 1;

  // get year to compare against from user
  printf("Which year would you like to see movies for? ");
  clearInput();
  scanf("%d", &y);

  // move through linked list, compare against provided year
  struct film *temp = f;
  while (temp != NULL) {
    if (temp->year == y && y != 0) {
      printf("%s\n", temp->title);
      printednothing = 0;
      temp = temp->next;
    } else {
      temp = temp->next;
    }
  }

  // if nothing got printed going through the list, tell the user
  if (printednothing == 1) printf("No data about movies released in year %d", y);
  printf("\n");
}

/**************************************************************************
  Title: copyFilm
  Description: duplicates and returns a provided film node.
***************************************************************************/
struct film *copyFilm(struct film *source) {
  struct film *node = (struct film *) calloc(1, sizeof(struct film));

  // title
  node->title = (char *) calloc(strlen(source->title) + 1, sizeof(char));
  strcpy(node->title, source->title);
  // node->title = source->title;

  // year
  node->year = source->year;

  //languages
  node->languages = (char **) calloc(5, sizeof(char*));
  for (int i = 0; i < 5; ++i) {
     node->languages[i] = (char *) calloc(strlen(source->languages[i] + 1), sizeof(char));
     strcpy(node->languages[i], source->languages[i]);
    // node->languages[i] = source->languages[i];
  }

  // rating
  node->rating = source->rating;
  node->next = NULL;

  return node;
}

/**************************************************************************
  Title: highestRated
  Description: handles the program option of printing the highest rated
               movies of a given year.
***************************************************************************/
void highestRated(struct film *f) {
  struct film *ratings = copyFilm(f);
  struct film *temp = f;

  // create a linked list with all the highest rated movies of a given year
  while (temp != NULL) {
    if (compareYears(ratings, temp) == 0) copyPush(ratings, temp);
    temp = temp->next;
  }

  // print all those highly rated movies.
  while (ratings != NULL) {
    if (ratings->year == 0) {
      ratings = ratings->next;
    } else {
      printf("%d %.1f %s\n", ratings->year, ratings->rating, ratings->title);
      ratings = ratings->next;
    }
  }
  printf("\n");
  free(ratings);
}

/**************************************************************************
  Title: compareYears
  Description: compares each each movie for year released, if same compares
               their ratings and the one with the bigger number gets to live
               in my badly constructed ratings linked list.
***************************************************************************/
int compareYears(struct film *dest, struct film *source) {
  struct film *temp = dest;

  while (temp != NULL) {
    if (temp->year == source->year) {
      if (temp->rating < source->rating) {
        strcpy(temp->title, source->title);
        temp->rating = source->rating;
      }
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

/**************************************************************************
  Title: copyPush
  Description: "pushes" a copied node onto a linked list.
***************************************************************************/
void copyPush(struct film *dest, struct film *source) {
  // duplicate the source node to new node
  struct film *node = copyFilm(source);

  // place it at the tail of destination linked list
  if (dest->next == NULL) {
    dest->next = node;
  } else {
    struct film *temp = dest;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = node;
  }
}

/**************************************************************************
  Title: moviesByLanguage
  Description: Prints all movies with a specified language.
***************************************************************************/
void moviesByLanguage(struct film *f){
  // get language from user
  char temp[20];
  printf("Which language would you like to see movies for? ");
  clearInput();
  scanf("%s", temp);
  int printedsomething = 0;

  // navigate through linked list and compare each language to user provided lang.
  struct film *nav = f;
  while (nav != NULL) {
    for (int i = 0; i < nav->nLang; ++i) {
      // if it's the same lang, print that bad boi
      if (strcmp(nav->languages[i], temp) == 0) {
        printedsomething = 1;
        printf("%s\n", nav->title);
      }
    }
    nav = nav->next;
  }

  // worst case scenario, let the user know we've failed them.
  if (printedsomething == 0) {
    printf("No data found for movies released in %s\n", temp);
  }
  printf("\n");
}

/**************************************************************************
  Title: printFilms
  Description: prints the contents of each film object in a film array
***************************************************************************/
void printFilms(struct film *films) {
  while (films != NULL) {
    printFilm(films);
    films = films->next;
  }
}

/**************************************************************************
  Title: printFilm
  Description: prints the contents of an individual film object
***************************************************************************/
void printFilm(struct film *f) {
  printf("%s, %d, ", f->title, f->year);

  for (int i = 0; i < f->nLang; ++i) {
    printf("%s ", f->languages[i]);
  }

  printf(", %f\n", f->rating);
}

/**************************************************************************
  Title:
  Description:
***************************************************************************/
struct film *extractData(char *filename) {
  FILE *data = fopen(filename, "r");
  char *temp = NULL;
  size_t len = 0;
  ssize_t nread;
  struct film *head = NULL;

  // go line by line through provided .csv and build the linked list.
  while ((nread = getline(&temp, &len, data)) != -1) {
    struct film *node = newNode(temp);

    if (head == NULL) {
      head = node;
    } else {
      struct film *nav = head;
      while (nav->next != NULL) {
        nav = nav->next;
      }
      nav->next = node;
    }
  }

  // clean up
  free(temp);
  fclose(data);

  return head;
}

/**************************************************************************
  Title: newNode
  Description: creates a new Film node from data provided in a string.
***************************************************************************/
struct film *newNode(char *source) {
  struct film *f = (struct film *) calloc(1, sizeof(struct film));

  char *temp;

  // Title
  char *token = strtok_r(source, ",", &temp);
  f->title = (char *) calloc(strlen(token) + 1, sizeof(char));
  strcpy(f->title, token);

  // Year
  token = strtok_r(NULL, ",", &temp);
  f->year = atoi(token);

  // Languages
  token = strtok_r(NULL, ",", &temp);
  f->nLang = 0;
  f->languages = getLanguages(token,&f->nLang);

  // Rating
  token = strtok_r(NULL, "\n", &temp);
  f->rating = strtof(token, NULL);


  return f;
}

/**************************************************************************
  Title: getLanguages
  Description:
***************************************************************************/
char **getLanguages(char *source, int *nLang) {
  // 2D char array to store our strings
  char **langs = (char **) calloc(5, sizeof(char *));
  for (int i = 0; i < 5; ++i) {
    langs[i] = (char *) calloc(20, sizeof(char));
  }

  char *temp = (char *) calloc(strlen(source + 1), sizeof(char *));
  int count = 0;

  // strip [] from source string.
  for (long unsigned int i = 0; i < strlen(source); ++i) {
    if (source[i] != 91 && source[i] != 93) {
      temp[count] = source[i];
      ++count;
    }
  }

  // create tokens from language string and assign individually to array
  char *token = strtok(temp, ";");
  while (token != NULL) {
    strcpy(langs[*nLang], token);
    (*nLang)++;
    token = strtok(NULL, ";");
  }

  free(temp);
  return langs;
}

/**************************************************************************
  Title: listSize
  Description: returns the number of nodes in a linked list
***************************************************************************/
int listSize(struct film *f) {
  int count = 0;
  struct film *temp = f;

  while (temp != NULL) {
    count++;
    temp = temp->next;
  }

  return count;
}

/**************************************************************************
  Title: clearInput
  Description: "empties" the input buffer.
***************************************************************************/
void clearInput() {
  while (getchar() != '\n');
}

/**************************************************************************
  Title: freeFilms
  Description: frees memory allocated to a film linked list.
***************************************************************************/
void freeFilms(struct film *f) {
  while (f != NULL) {
    struct film *temp = f;
    f = f->next;
    free(temp->title);
    for (int i = 0; i < 5; ++i) {
      free(temp->languages[i]);
    }
    free(temp->languages);
    free(temp);
  }
}

/**************************************************************************
  Title: freeNoString
  Description: Frees individual nodes from a linked list except ones that
               may just be pointing to another linked list. Yea I've got some
               bad code in here, whatever.
***************************************************************************/
void freeNoString(struct film *f) {
  while (f != NULL) {
    struct film *temp = f;
    f = f->next;
    free(temp);
  }
}
