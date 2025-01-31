#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  FILE *readFile, *writeFile;
  int ch;
  struct stat fileStat;
  
  if(argc != 3) {
    fprintf(stderr, "Invalid args\n");
    exit(1);
  }
  
  readFile = fopen(argv[1], "r");
  
  if(readFile == NULL) {
    perror("Fail to open\n");
    exit(1);
  }
  
  if(stat(argv[1], &fileStat) != 0) {
    perror("Fail to get info\n");
    exit(1);
  }
  
  writeFile = fopen(argv[2], "w");
  
  if(writeFile == NULL) {
    perror("Fail to open\n");
    fclose(readFile);
    exit(1);
  }
  
  
  while((ch = fgetc(readFile)) != EOF) {
    if (fputc(ch, writeFile) == EOF) {
      perror("Fail to write\n");
      fclose(readFile);
      fclose(writeFile);
      exit(1);
    }
  }
  
  
  if (ferror(readFile)) {
    perror("Fail to read file");
    fclose(readFile);
    fclose(writeFile);
    exit(1);
  }
  
  fclose(readFile);
  fclose(writeFile);
  
  if(chmod(argv[2], fileStat.st_mode)  != 0) {
    perror("Fail to set access");
    exit(1);
  }
  
  return 0;
}
