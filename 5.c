#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void dirList(const char *dirPath) {
  DIR *dir;
  struct dirent *entry;
  
  dir = opendir(dirPath);
  if (dir == NULL){
    perror("Fail to open\n");
    exit(1);
  }
  
  printf("Catalog %s:\n", dirPath);
  while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
  }
  closedir(dir);
}
int main(int argc, char *argv[]){
  if (argc != 2){
    printf("Invalid arguments\n");
    exit(1);
  }
  
  dirList(".");
  
  dirList(argv[1]);
  
  exit(0);
}
