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
      buffer_2[length-level] = charset[i];
      recursion(charset,charset_length,length,buffer_2,level-1);
    }
  } else {
    printf("%s\n",buffer);
  }
  free(buffer_2);
}

typedef struct {
  char * name;
  char * charset;
  unsigned int charset_length;
} known_charset;

# define KNOWN_CHARSETS 4
known_charset dico [] = {
  {"ascii"," !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",95},
  {"digits","0123456789",10},
  {"hexa","0123456789abcdef",16},
  {"HEXA","0123456789ABCDEF",16}
};

int match_known_charset(char * name,unsigned int * charset_length, char ** charset)
{
  unsigned int i = 0;
  for (i=0;i<KNOWN_CHARSETS; i++)
  {
    if (strcmp(dico[i].name,name) == 0)
    {
      *charset = malloc(dico[i].charset_length);
      strncpy(*charset,dico[i].charset,dico[i].charset_length);
      *charset_length = dico[i].charset_length;
      return EXIT_SUCCESS;
    }
  }

  return EXIT_FAILURE;
}

int main (int argc, char * argv[])
{
  char * charset = NULL;
  unsigned int charset_length;
  unsigned int length;
  unsigned int start_level;
  char * buffer;

  if ((argc < 3 )||(argc > 4))
  {
    printf("Usage : %s <charset> <length> [prefix]\n",argv[0]);
    return EXIT_FAILURE;
  }
  if (match_known_charset(argv[1],&charset_length,&charset) == EXIT_FAILURE)
  {
    charset_length = strlen(argv[1]);
    charset = malloc(charset_length);
    strncpy(charset,argv[1],charset_length);
  }

  length = atoi(argv[2]);

  buffer = malloc(length);
  while (buffer == NULL)
  {
    buffer = malloc(length);
    sleep(0.2);
  }
  memset(buffer,66,length);

  if (argc == 4)
  {
    if (strlen(argv[3]) > length)
    {
      fprintf(stderr,"prefix too long\n");
      return EXIT_FAILURE;
    }
    strcpy(buffer,argv[3]);
    start_level = length-strlen(argv[3]);
  } else {
    start_level = length;
  }


  /*
  HUURRRR DUUUURRRR RDEPR DERP
  fprintf(stderr,"Charset : «%s»\nCharset length : %d\nLength : %d\n",charset,charset_length,length);
  */
  
  recursion(charset,charset_length,length,buffer,start_level);

  free(buffer);
  free(charset);

  return EXIT_SUCCESS;
}
