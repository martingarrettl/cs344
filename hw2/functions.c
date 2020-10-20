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
  Title:
  Description:
***************************************************************************/
void userOptions(int *end) {
  int option;

  printf("1. Select file to process\n");
  printf("2. Exit\n");
  printf("Enter option 1 or 2: ");
  scanf("%d", &option);
  printf("\n");
  checkOptions(option, end);
  clearInput();
}
/**************************************************************************
  Title:
  Description:
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
  Title:
  Description:
***************************************************************************/
void selectFileProcess() {
  int option;

  printf("Which file do you want to process?\n");
  printf("\t1. Select largest file\n");
  printf("\t2. Select smallest file\n");
  printf("\t3. Specify file by filename\n");
  printf("Enter option 1-3: ");
  scanf("%d", &option);
  printf("\n");
  checkSelectFile(option);

}
/**************************************************************************
  Title:
  Description:
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
  Title:
  Description:
***************************************************************************/
void processLargest() {
  char *dirname = createFoldername();
  char *largest = findLargest();

  printf("Now processing the largest file, named %s\n", largest);

  processCSV(largest, dirname);
  printf("Created directory with name %s\n", dirname);

  printf("\n");
  free(largest);
  free(dirname);
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
void processSmallest() {
  char *dirname = createFoldername();
  char *smallest = findSmallest();

  printf("Now processing the smallest file, named %s\n", smallest);

  processCSV(smallest, dirname);
  printf("Created directory with name %s\n", dirname);

  printf("\n");
  free(smallest);
  free(dirname);
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
void processFilename() {
  char *dirname = createFoldername();
  char filename[25];

  printf("Enter the complete filename: ");
  scanf("%s", filename);

  int exists = findFilename(filename);

  if (exists == 1) {
    printf("Now processing the file named %s\n", filename);
    processCSV(filename, dirname);
    printf("Created directory with name %s\n", dirname);
  } else  {
    printf("ERROR: File named \"%s\" not found.\n\n", filename);
    selectFileProcess();
  }

  free(dirname);
}
/**************************************************************************
  Title:
  Description:
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
  Title:
  Description:
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
  Title:
  Description:
***************************************************************************/
int findFilename(char *filename) {
  int a = 0; // int as bool to return

  char *tempstr = (char *)calloc(1, sizeof(filename) + sizeof(SUFFIX) + 5);
  strcpy(tempstr, filename);
  strcat(tempstr, SUFFIX);
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

  closedir(wd);
  free(tempstr);

  return a;
}
/**************************************************************************
  Title:
  Description:
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
  Title:
  Description:
***************************************************************************/
void processCSV(char *filename, char *dirname) {
  // turn the filename into a usable path
  char *dPath = (char *)calloc(1, strlen(dirname) + 12);
  strcpy(dPath, "./");
  strcat(dPath, dirname);
  printf("filepath: %s\n", dPath);

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

    // make or append to corresponding txt file and then adjust permissions.
    FILE *f = fopen(year, "a+");
    token = strtok_r(temp, ",", &tempstr);
    duplicate = (char *)realloc(duplicate, strlen(token) + strlen("\n\0") + 1);
    strcpy(duplicate, token);
    strcat(duplicate, "\n\0");
    fputs(duplicate, f);

    fclose(f);
    int permissions = chmod(year, 0640);
    free(duplicate);
  }

  fclose(data);
  free(year);
  free(dPath);
}
/**************************************************************************
  Title: clearInput
  Description: "empties" the input buffer.
***************************************************************************/
void clearInput() {
  while (getchar() != '\n');
}
