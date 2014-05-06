# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# define BUFFAH_SIZE 64
unsigned char val(unsigned char x){if (x < 0x3a) {return x % 0x30;} else {return (x % 0x20)+9;}}
int main(int argc, char * argv[])
{
  unsigned char * buffer = NULL;
  ssize_t length = 0;
  unsigned int i = 0;
  int fd = 0;
  if (argc>1){fd = open(argv[1],'r');}
  buffer = malloc(BUFFAH_SIZE*sizeof(unsigned char));
  while ((length = read((int)fd,buffer,BUFFAH_SIZE)) > 0)  {
    for (i=0;i<length;i+=2) {
      putchar((val(buffer[i]) << 4)+val(buffer[i+1])); } }
  return EXIT_SUCCESS;}
