# include <unistd.h>
# include "gf256.c"
# ifdef usecolor
# include "../rainbow.c"
# else
unsigned char color[256][3];
# endif

int main()
{
  unsigned int i,j;
# ifndef usecolor
  for (i=0;i<256;i++) {
    color[i][0] = (unsigned char)i;
    color[i][1] = (unsigned char)i;
    color[i][2] = (unsigned char)i;
  }
# endif
  write(1,"P6 256 256 255 ",15);
  for (i=0;i<256;i++) {
    for (j=0;j<256;j++) {
# ifndef usecolor
      write(1,&color[gf_pow(j+1,i)],3);
# else 
      write(1,&color[gf_pow(j+1,i)],3);
# endif
    }
  }
}
