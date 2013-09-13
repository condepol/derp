# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
void recursion(unsigned int nwords,
    char ** words,
    char separator,
    char ** buffer,
    unsigned int length,
    unsigned int level)
{
  unsigned int i = 0;
  if (level) {
    /* recall */
    for (i=0;i<nwords;i++)
    {
      buffer[level-1] = words[i];
      recursion(nwords,words,separator,buffer,length,level-1);
    }
  } else {
    /* render */
    for (i=0;i<length;i++)
    {
      printf("%s",buffer[i]);
      if (i==length-1)
      {puts("");}
      else
      {putchar(separator);}
    }
  }
}

int main (int argc, char * argv[])
{
  unsigned int length;
  char separator;
  char ** buffer = NULL;

  if (argc < 5)
  {
    printf("Usage : %s <word1> <word2> ... <wordn> <length> <separator>\n",argv[0]);
    return EXIT_FAILURE;
  }

  separator = argv[argc-1][0];
  length = atoi(argv[argc-2]);

  buffer = malloc(length*sizeof(char *));

  fprintf(stderr,"%20s : «%c»\n%20s : %d\n%20s : %d\n",
      "separator",separator,
      "length",length,
      "nwords",argc-3);
  recursion(argc-3,&argv[1],separator,buffer,length,length);
  free(buffer);
  return EXIT_SUCCESS;
}
