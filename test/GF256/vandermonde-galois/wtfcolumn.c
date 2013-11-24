# include <stdio.h>
# include <stdlib.h>
# include "gf256.c"

int main(int argc, char * argv[])
{
  unsigned int i,j;
  i = 213;
  printf("256 values of column %i :\n",i);
  for (j=0;j<256;j++) {
    if (j%0x10 == 0) {puts("");}
    printf("%02x ",gf_pow(i+1,j));
  }
  puts("");
}
