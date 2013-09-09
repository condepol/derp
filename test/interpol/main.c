# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* fill <len> bytes of <buffer> with rand() values */
unsigned char * random_fill(unsigned char * buffer, unsigned int len)
{
  unsigned int i = 0;
  for (i = 0; i < len; i++)
  {
    buffer[i] = (unsigned char)rand();
  }
  return buffer;
}

/* return true if c is printable, non-newline*/
unsigned int iscool(char c){return ((c > 0x20) & (c < 0x7f));}

/* 49 45 46 48 47 <-- dump a buffer to stdout */
void hexdump (unsigned char * buffer, unsigned int length)
{
  unsigned int index = 0;
  for (index = 0; index < length; index++) {printf("%02x ",buffer[index]);}
}

/* ada.\ae.. <-- dump printable parts of a buffer */
void ascdump (unsigned char * buffer, unsigned int length)
{
  unsigned int index = 0;
  for (index = 0; index < length; index++)
  {
    if (buffer[index])
    {
      printf("%c",buffer[index]);
    } else {
      printf(".");
    }
  }
}

unsigned char power(unsigned char v, unsigned int pow)
{
  unsigned char val = v;
  unsigned int i = 0;
  if (pow != 0)
  {
    for (i=1; i<pow; i++)
    {
      val *= v ;
    }
    return val;
  } else {
    return 1;
  }
}

unsigned char eval_buffer(unsigned char * poly, unsigned int index)
/* return sum(  p[i] *(index**i) for i in [0..index]) */
{
  unsigned char r = 0;
  unsigned int i = 0;
  for (i=0; i < index + 1; i++)
  {
    r += poly[i] * power(index,i);
  }
  return r;
}

unsigned char eval_poly(unsigned char * poly, unsigned int polylength, unsigned char val)
{
  unsigned char r = 0;
  unsigned int i = 0;
  for (i=0; i<polylength; i++)
  {
    r += poly[i] * power(val,i);
  }
  return r;
}

int main(int argc, char * argv[])
{
  unsigned char * data = NULL;
  unsigned char * poly = NULL;
  unsigned char * outp = NULL;
  unsigned int len = 12;
  unsigned int i = 0;

  /* if possible, use user defines array length */
  if (argc > 1) {len = atoi(argv[1]);}

  /* malloc byte arrays */
  data = malloc(len);
  poly = malloc(len);
  outp = malloc(len);

  /* randomly fill first buffer */
  /*srand(time(NULL));*/
  srand(0x42);
  data = random_fill(data,len);

  /* print data */
  printf("data : "); hexdump(data,len);printf("\n");

  /* compute polynom */
  for (i=0; i<len; i++)
  {
    if (i>0)
    {
      poly[i] = eval_buffer(data,i) - eval_buffer(data,i-1);
    } else {
      poly[i] = eval_buffer(data,i);
    }
  }
  printf("poly : "); hexdump(poly,len);printf("\n");

  /* evalue polynom */
  for (i=0; i<len; i++)
  {
    outp[i] = eval_poly(poly,len,i);
  }
  
  printf("outp : "); hexdump(outp,len);printf("\n");
  
  return EXIT_SUCCESS;
}
