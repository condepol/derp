#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void public (char* args) {
  char buff[12];
  strcpy(buff,args);
  printf("public\n");
}

void secret(void) {
  printf("secret\n");
}
int main (int argc, char * argv[]) {
  if (getuid() == 0) {
    secret();
  } else {
    public(argv[1]);
  }
  return EXIT_SUCCESS;
}
