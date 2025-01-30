#include <stdio.h>
#include <stdlib.h>

void waitKey(){
  printf("Click button\n");
  getchar();
}

int main(int argc, char *argv[]) {
  FILE *file;
  int ch, lineCnt = 0, allLines;
  
  if(argc != 3) {
  fprintf(stderr, "Use as argument filename and count of rows\n");
  exit(1);
  }
  
  file = fopen(argv[1], "r");
  
  if(file == NULL) {
  perror("Fail to open\n");
  exit(1);
  }
  
  allLines = atoi(argv[2]);
  
  while((ch = fgetc(file)) != EOF) {
    putchar(ch);
    if(ch == '\n'){
      lineCnt++;
      if (allLines != 0 && lineCnt == allLines){
        waitKey();
        lineCnt = 0;
      }
    }
  }
  
  if (ferror(file)) {
    perror("Fail to read file");
    fclose(file);
    exit(1);
  }
  
 
  fclose(file);
  return 0;
}
