# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# define BUFFAH_SIZE 64
unsigned char val(unsigned char x)
{
  if (x < 0x3a)
  {
    /* it's a digit */
    return (x % 0x30);
  } else {
    /* it's a letter*/
    return (x % 0x20)+9;
  }
}

int main(int argc, char * argv[])
{

  unsigned char buffer[BUFFAH_SIZE];
  ssize_t length = 0;
  int i = 0;
  int fd = 0;

  /* input is stdin or argv[1] */
  if ( argc > 1 ) { fd = open(argv[1],'r'); }

  while ((length = read((int)fd,buffer,BUFFAH_SIZE)) > 0)  {

    for (i=0;i < length-1;i+=2) {
      putchar((val(buffer[i]) << 4)+val(buffer[i+1])); 
    } 
  }
  return EXIT_SUCCESS;
}
