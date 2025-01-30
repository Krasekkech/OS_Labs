#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file;
  int ch;
  
  if(argc !=2) {
  fprintf(stderr, "Use as argument filename\n");
  exit(1);
  }
  
  file = fopen(argv[1], "w");
  
  if(file == NULL) {
  perror("Fail to open\n");
  exit(1);
  }
  
  printf("Write letters (CTRL-F for finish)\n");
  while((ch = getc(stdin)) != EOF) {
    if(ch == 6){break;}
  
    if(fputc(ch, file) == EOF) {
    perror("Fail to write in file\n");
    exit(1);
    }
  }
  
  if(fclose(file) == EOF) {
  perror("Fail to close file");
  exit(1);
  }
  
  return 0;
}
