# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void recursion(char * charset, unsigned int charset_length, unsigned int length, char * buffer, unsigned int level)
{
  char * buffer_2 = NULL;
  unsigned int i = 0;
  buffer_2 = malloc(length+1);
  while (buffer_2 == NULL) {
    sleep(0.2); // olol derp derp
    buffer_2 = malloc(length+1);
  }
  memset(buffer_2,0,length+1);
  strncpy(buffer_2,buffer,length);

  if (level)
  {
    for (i=0;i<charset_length;i++)
    {
      buffer_2[level-1] = charset[i];
      recursion(charset,charset_length,length,buffer_2,level-1);
    }
  } else {
    printf("%s\n",buffer);
  }
  free(buffer_2);
}

int main (int argc, char * argv[])
{
  char * charset;
  unsigned int charset_length;
  unsigned int length;
  char * buffer;

  if (argc != 3)
  {
    printf("Usage : %s <charset> <length>\n",argv[0]);
    return EXIT_FAILURE;
  }

  charset_length = strlen(argv[1]);
  charset = malloc(charset_length);
  strncpy(charset,argv[1],charset_length);

  length = atoi(argv[2]);

  buffer = malloc(length);
  memset(buffer,66,length);


  /*
  HUURRRR DUUUURRRR RDEPR DERP
  fprintf(stderr,"Charset : «%s»\nCharset length : %d\nLength : %d\n",charset,charset_length,length);
  */
  
  recursion(charset,charset_length,length,buffer,length);

  free(buffer);
  free(charset);

  return EXIT_SUCCESS;
}
