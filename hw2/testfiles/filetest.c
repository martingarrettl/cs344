#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
	int file_descriptor;
	char* newFilePath = "./test.csv";

  // flags: the arguments are OR-ed togther
  // O_RDWR reading and writing
  // O_CREAT create an empty file if the file doesn't exist
  // O_TRUNC truncate the file if it already exists
  // mode:
  // 0600 Owner can read and write the file
	file_descriptor = open(newFilePath, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (file_descriptor == -1){
		printf("open() failed on \"%s\"\n", newFilePath);
		perror("Error");
		exit(1);
	}

	printf("file_descriptor = %d\n", file_descriptor);

	return 0;
}
