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
  checkSelectFile(option);
  // clearInput();
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
  char *fname = (char *)calloc(1, sizeof(largest) + 17);

  printf("Now processing the largest file, named %s\n", largest);
  // make new string with ./ so largest is actually an openable filename
  strcpy(fname, "./");
  strcat(fname, largest);
  strcat(fname, "\0");

  int file = open(fname, O_RDONLY);
  if (file  == -1) {
    printf("open() failed on \"%s\"\n", fname);
    perror("Error");
    exit(1);
  }

  printf("Created directory with name %s\n", dirname);

  close(file);
  free(fname);
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
  printf("Created directory with name %s\n", dirname);

  free(smallest);
  free(dirname);
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
void processFilename() {
  char *dirname = createFoldername();
  char filename[120];

  printf("Enter the complete filename: ");
  scanf("%s", filename);

  printf("Now processing the file named %s\n", filename);
  printf("Created directory with name %s\n", dirname);

  free(dirname);
}
/**************************************************************************
  Title:
  Description:
***************************************************************************/
char *findLargest(){
  char *largest = (char *)malloc(4);

  // open working directory
  DIR* wd = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  long int current = 0;

  // loop over all the entries in the directory
  while((aDir = readdir(wd))) {
    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
      stat(aDir->d_name, &dirStat);
      if (dirStat.st_size > current) {
        current = dirStat.st_size;
        largest = (char *)realloc(largest, sizeof(aDir->d_name));
        strcpy(largest, aDir->d_name);
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

  // open working directory
  DIR* wd = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  long int current = 999999;

  // loop over all the entries in the directory
  while((aDir = readdir(wd))) {
    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
      stat(aDir->d_name, &dirStat);
      if (dirStat.st_size < current) {
        current = dirStat.st_size;
        smallest = (char *)realloc(smallest, sizeof(aDir->d_name));
        strcpy(smallest, aDir->d_name);
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
  Title: clearInput
  Description: "empties" the input buffer.
***************************************************************************/
void clearInput() {
  while (getchar() != '\n');
}
