# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "crc32.c"
# define BUFFER_SIZE 16

int isnotin (unsigned int n, unsigned int * v, unsigned int len)
{
  unsigned int i = 0;
  for (i=0;i<len;i++)
  {
    if (v[i] == n) {return EXIT_SUCCESS;}
  }
  return EXIT_FAILURE;
}

unsigned char * print_vector (unsigned int * vector, unsigned int len)
{
  unsigned char * output = NULL;
  unsigned int i = 0;
  output = malloc(len*9*sizeof(unsigned char));
  memset(output,0,len*9*sizeof(unsigned char));
  for (i=0; i<len; i++)
  {
    sprintf((char * restrict)&output[9*i],"%08x ",vector[i]);
  }
  return output;
}
int main (int argc, char * argv[])
{
  time_t t = 0;
  unsigned char * buffer = NULL;
  unsigned int crc = 0;
  unsigned int length = 1;
  unsigned int * wanted = NULL;
  unsigned int column = 0;
  unsigned int counter = 0;

  printf("%d\n",argc);
  if (argc > 1)
  {
    /* init stuff */
    
    wanted = malloc((argc-1)*sizeof(unsigned int));
    for (counter = 1;counter < argc; counter++)
    {
      wanted[counter-1] = strtoul(argv[counter],NULL,16);
    }

    t = time(NULL);
    buffer = malloc(BUFFER_SIZE*sizeof(unsigned char));
    memset(buffer,0,BUFFER_SIZE*sizeof(unsigned char));
    buffer[0] = ' ';

    printf("Bruteforcing buffer while crc32(buffer) not in %s\n",(char * restrict)print_vector(wanted,argc-1));
    /* bruteforce buffer*/
    
    crc = crc32(0xffffffffU, buffer, length);
    while (isnotin(crc,wanted,argc-1))
    { 
      if ((counter % 0x1000000)==0) 
      {
        printf("\x1b[0G%02x %08x [%d] «%s»",counter >> 24,crc,length,buffer);
        fflush(stdout);
      }
      counter++;
      /* update buffer */
      while (buffer[column] > 0x7d)
      {
        /* reset from max to min*/
        buffer[column] = 0x20;
        column++;
        if (buffer[column] == 0)
        {
          /* init from zero to min*/
          buffer[column] = 0x20;
          length++;
        }
      }
      buffer[column]++;
      column = 0;
      /* compute crc */
      crc = crc32(0xffffffffU, buffer, length);
    }


    printf("\x1b[0Gcrc32(«\x1b[32m%s\x1b[0m») = %08x%30s\n",buffer,crc,"");
    printf("%d seconds.\n",(int)difftime(time(NULL),t));
    return EXIT_SUCCESS;
  } else {
    printf("argc : %d\n",argc);
    puts("./executable cafebabe");
    return EXIT_FAILURE;
  }
}
