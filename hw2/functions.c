/**************************************************************************
  Author: Garrett Martin
  Email: martgarr@oregonstate.edu
  Date: 18/10/2020
  Class: CS344
  Section: 001
  Assignment: 2 - Files & Directories
***************************************************************************/

#include "functions.h"

/**************************************************************************
  Title: userOptions
  Description: prints the main menu options available to the user and
               accepts their choice.
***************************************************************************/
void userOptions(int *end) {
  int option;

  char *temp = NULL, *temp2;
  size_t len = 0;
  ssize_t read;

  printf("\t1. Select file to process\n");
  printf("\t2. Exit\n");
  printf("Enter option 1 or 2: ");

  // i use this more convoluted method to get an int from user because i
  // kept getting a buffer underflow error later in the program with scanf.
  read = getline(&temp, &len, stdin);
  temp = strtok_r(temp, "\n", &temp2);
  option = atoi(temp);
  printf("\n");

  free(temp);
  checkOptions(option, end);
}
/**************************************************************************
  Title: checkOptions
  Description: takes a user main menu option and directs it accordingly.
***************************************************************************/
void checkOptions(int opt, int *end) {
  switch(opt) {
    case 1:
      selectFileProcess();
      break;
    case 2:
      *end = 1;
      break;
    default:
      printf("Invalid input, please try again\n\n");
      userOptions(end);
      break;
  }
}
/**************************************************************************
  Title: selectFileProcess
  Description: Prints the list of processing options available to the user
               and allows them to select a choice.
***************************************************************************/
void selectFileProcess() {
  int option;

  char *temp = NULL, *temp2;
  size_t len = 0;
  ssize_t read;

  printf("Which file do you want to process?\n");
  printf("\t1. Select largest file\n");
  printf("\t2. Select smallest file\n");
  printf("\t3. Specify file by filename\n");
  printf("Enter option 1-3: ");
  read = getline(&temp, &len, stdin);
  temp = strtok_r(temp, "\n", &temp2);
  option = atoi(temp);
  checkSelectFile(option);

  free(temp);
}
/**************************************************************************
  Title: checkSelectFile
  Description: takes user processing choice and directs it accordingly.
***************************************************************************/
void checkSelectFile(int opt) {
  switch(opt) {
    case 1:
      processLargest();
      break;
    case 2:
      processSmallest();
      break;
    case 3:
      processFilename();
      break;
    default:
      printf("Invalid option, please try again\n");
      selectFileProcess();
      break;
  }
}
/**************************************************************************
  Title: processLargest
  Description: handles the work for automatically finding the largest
               csv and extracting the movie data from it.
***************************************************************************/
void processLargest() {
  char *dirname = createFoldername();
  char *largest = findLargest();

  printf("\n");
  printf(" - Now processing the largest file, named %s\n", largest);

  processCSV(largest, dirname);
  printf(" - Created directory with name %s\n", dirname);

  printf("\n");
  free(largest);
  free(dirname);
}
/**************************************************************************
  Title: processSmallest
  Description: handles the work for automatically finding the smallest
               csv and extracting the movie data from it.
***************************************************************************/
void processSmallest() {
  char *dirname = createFoldername();
  char *smallest = findSmallest();

  printf("\n");
  printf(" - Now processing the smallest file, named %s\n", smallest);

  processCSV(smallest, dirname);
  printf(" - Created directory with name %s\n", dirname);

  printf("\n");
  free(smallest);
  free(dirname);
}
/**************************************************************************
  Title: processFilename
  Description: handles the work for extracting movie data from a user
               provided .csv
***************************************************************************/
void processFilename() {
  char *dirname = createFoldername();
  char *filename = NULL;
  size_t len = 0;
  ssize_t read;
  int exists = 0;

  printf("Enter the complete filename e.g. \"movies_sample_1.csv\": ");
  while ((read = getline(&filename, &len, stdin)) != -1) {
    if (read > 0) {
      exists = findFilename(filename);
    }
    break;
  }
  printf("\n");

  if (exists == 1) {
    char *filepath = (char *)calloc(1, strlen(filename) + 1);
    strncpy(filepath, filename, strlen(filename) - 1);
    strcat(filepath, "\0");
    printf(" - Now processing the file named %s\n", filepath);
    processCSV(filepath, dirname);
    printf(" - Created directory with name %s\n", dirname);
    free(filepath);
  } else  {
    printf(" - ERROR: File named \"%s\" was not found.\n\n", filename);
    selectFileProcess();
  }

  printf("\n");
  free(filename);
  free(dirname);
}
/**************************************************************************
  Title: findLargest()
  Description: returns a string corresponding to the largest .csv file
               with movies_ prefix in working dir
***************************************************************************/
char *findLargest(){
  char *largest = (char *)malloc(4);
  char filetype [] = ".csv";
  char *temp;

  // modified code from an example on "Exploration: Directories" page
  // open working directory
  DIR* wd = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  long int current = 0;

  // loop over all the entries in the directory
  while((aDir = readdir(wd))) {
    // make sure the file starts with movies_
    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
      // make sure it's of type .csv
      temp = strstr(aDir->d_name, filetype);
      if (temp != NULL){
       stat(aDir->d_name, &dirStat);
       // we want the biggest one
        if (dirStat.st_size > current) {
          current = dirStat.st_size;
          largest = (char *)realloc(largest, sizeof(aDir->d_name));
          strcpy(largest, aDir->d_name);
        }
      }
    }
  }

  closedir(wd);

  return largest;
}
/**************************************************************************
  Title: findSmallest
  Description: returns a string corresponding to the smallest .csv file
               with movies_ prefix in working dir
***************************************************************************/
char *findSmallest(){
  char *smallest = (char *)malloc(4);
  char filetype [] = ".csv";
  char *temp;

  // modified code from an example on "Exploration: Directories" page
  // open working directory
  DIR* wd = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  long int current = 999999;

  // loop over all the entries in the directory
  while((aDir = readdir(wd))) {
    // make sure the file starts with movies_
    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
      // make sure it is of type .csv
      temp = strstr(aDir->d_name, filetype);
      if (temp != NULL){
        stat(aDir->d_name, &dirStat);
        // we want the smallest one
        if (dirStat.st_size < current) {
          current = dirStat.st_size;
          smallest = (char *)realloc(smallest, sizeof(aDir->d_name));
          strcpy(smallest, aDir->d_name);
        }
      }
    }
  }

  closedir(wd);

  return smallest;
}
/**************************************************************************
  Title: findFilename
  Description: Returns a boolean value based on whether a user provided
               filename exists within the working directory.
***************************************************************************/
int findFilename(char *filename) {
  int a = 0; // int as bool to return

  char *tempstr = (char *)calloc(1, strlen(filename) + 1);
  strncpy(tempstr, filename, strlen(filename) - 1);
  strcat(tempstr, "\0");

  // open working directory
  DIR* wd = opendir(".");
  struct dirent *aDir;

  // loop over directory and compare each file against provided filename
  while((aDir = readdir(wd))) {
    if(strncmp(tempstr, aDir->d_name, strlen(tempstr)) == 0) {
      a = 1;
    }
  }

  // if it ain't got the .csv filetype get that thing outta here
  char filetype [] = ".csv";
  char *temp;
  if ((temp = strstr(tempstr, filetype)) == NULL) {
    a = 0;
  }

  closedir(wd);
  free(tempstr);

  return a;
}
/**************************************************************************
  Title: createFoldername
  Description: returns a string corresponding to a a folder name with
               a fixed prefix and a random number
***************************************************************************/
char *createFoldername() {
  char onid [] = "martgarr.movies.";
  int r = rand() % 9999;
  char *numstr = (char *)(calloc(1, 5));

  // formatted print to string of the value of r
  sprintf(numstr, "%d", r);
  strcat(numstr, "\0");

  // create a string of sufficient size to hold onid + random number
  char *str = (char *)calloc(1, sizeof(onid) + sizeof(numstr) + 1);
  strcpy(str, onid);
  strcat(str, numstr);
  strcat(str, "\0");

  free(numstr);
  return str;
}
/**************************************************************************
  Title: processCSV
  Description: Goes line by line through provided csv file and extracts
               the title of each movie and puts it into a .txt file in the
               provided directory according to the year of its release.
***************************************************************************/
void processCSV(char *filename, char *dirname) {
  // turn the filename into a usable path
  char *dPath = (char *)calloc(1, strlen(dirname) + 12);
  strcpy(dPath, "./");
  strcat(dPath, dirname);

  // create new directory w/ rwxr-x--- permissions
  int newdir = mkdir(dirname, 0750);

  char *year = (char *)calloc(1, strlen(dirname) + strlen("/1111.txt\0") + 1);
  FILE *data = fopen(filename, "r");
  char *temp;
  size_t len = 0;
  ssize_t nread;

  // get rid of that line with none of the GOOD data, that realLY REALLY GOOD DATA
    nread = getline(&temp, &len, data);
  // go line by line through source csv and output into corresponding txt files
  while ((nread = getline(&temp, &len, data)) != -1){
    // get the year the current line is associated with
    char *duplicate = (char *)calloc(1, strlen(temp) + 1);
    strcpy(duplicate, temp);
    char *tempstr;
    char *token = strtok_r(duplicate, ",", &tempstr);
    token = strtok_r(NULL, ",", &tempstr);

    // string stuff to make year a usable path
    strcpy(year, dirname);
    strcat(year, "/");
    strcat(year, token);
    strcat(year, ".txt\0");

    // make or append to corresponding txt file
    FILE *f = fopen(year, "a+");
    token = strtok_r(temp, ",", &tempstr);

    // repurpose string to format movie title string and append to doc
    duplicate = (char *)realloc(duplicate, strlen(token) + strlen("\n\0") + 1);
    strcpy(duplicate, token);
    strcat(duplicate, "\n\0");
    fputs(duplicate, f);

    // clean up any loose memory and adjust file permissions
    fclose(f);
    int permissions = chmod(year, 0640);
    free(duplicate);
  }

  fclose(data);
  free(temp);
  free(year);
  free(dPath);
}
