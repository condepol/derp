# define _ISOC99_SOURCE 
# include <unistd.h>
# include <math.h>
# include "../rainbow.c"
int main()
{
  unsigned int i,j;
  write(1,"P6 256 256 255 ",16);
  for (i=0;i<256;i++) {
    for (j=0;j<256;j++) {
      write(1,&color[(unsigned char)(unsigned long)pow((double)(j+1),(double)i)],3);
    }
  }
}
