# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

int main (int argc, char * argv[] )
{
  unsigned int i = 0;
  if (0) {puts("if(0) = True.");}
  if (1) {puts("if(1) = True.");}
  for (i=0;i<0x100;i++)
  {
    errno = i;
    printf("%d - ",i);
    fflush(stdout);
    perror("");
  }
  errno = 0;
  perror("derp");
  
  return EXIT_SUCCESS;
}
