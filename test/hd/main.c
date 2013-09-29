# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>

# define BUFFAH_SIZE 16

unsigned char hexa(unsigned char x){return (x+0x30)+((x>9)*0x27);}
unsigned char ch1(unsigned char x){if((x>0x1f)&&(x<0x7f)){return 32;}else{return hexa(x>>4);}}
unsigned char ch2(unsigned char x){if((x>0x1f)&&(x<0x7f)){return x;}else{return hexa(x%16);}}
unsigned int color(unsigned char x)
{
  switch (x>>5) {
    case 2:
      if (((x-1)%0x20)<0x1b) { return 4+(x>0x60)*2;}
      return 5;
    case 3:
      if (((x-1)%0x20)<0x1b) { return 4+(x>0x60)*2;}
      return 5;
    case 1:
      if (x%0x30<10) {return 1;}
      return 5;
    default:
      return 0;
  }
}

int main(int argc, char * argv[])
{
  unsigned char * buffer = NULL;
  ssize_t length = 0;
  unsigned int i = 0;
  int fd = 0;

  if (argc>1){fd = open(argv[1],'r');}

  buffer = malloc(BUFFAH_SIZE*sizeof(unsigned char));

  while ((length = read((int)fd,buffer,BUFFAH_SIZE)) > 0)
  {
    for (i=0;i<length;i++)
    {
      printf("\x1b[3%dm%c%c\x1b[0m",color(buffer[i]),ch1(buffer[i]),ch2(buffer[i]));
    }
    putchar(0x0a);
  }

  return EXIT_SUCCESS;
}
