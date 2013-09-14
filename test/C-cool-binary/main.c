# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

unsigned int hex_to_int(char h) {return (h<64)*(h-48)+(h>64)*(9+h%16);}
char int_to_hex(unsigned int i) {return (i+48)+(i>9)*7;}

int multi_hex_to_int(char * h, unsigned int length)
{
  unsigned int i = 0;
  unsigned int r = 0;
  for (i=0;i<length;i++)
  {
    r <<= 4;
    r += hex_to_int(h[i]);
  }
  return r;
}

char * uint_to_chars(unsigned int i)
{
  char * output = NULL;
  unsigned int z = 8;
  output = malloc(9);
  output[8] = 0;
  while (i)
  {
    output[--z] = int_to_hex(i%16);
    i>>=4;
  }
  return output;
}

int main(int argc, char * argv[])
{
  char * string = NULL;
  unsigned int i = 0;

  if (argc != 1)
  {
    printf("%s\n",argv[0]);
    errno = 130;
    perror("Moonlight sonata");
    return EXIT_FAILURE;
  }
  
  string = malloc(16);
  strncpy(string,"1e240\x00",6);
  printf("%s = %d\n",string,multi_hex_to_int(string,5));

  i = 0xfe1256ab;
  string = uint_to_chars(i);
  printf("%u = %s\n",i,string);
  free(string);

  return EXIT_SUCCESS;
}
