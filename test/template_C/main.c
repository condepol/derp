# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <stdlib.h>
# include <unistd.h>

int main(int argc, char * argv[])
{
  unsigned int i = 0;
  if (argc < 4)
  {
    errno = 130;
    perror("Moonlight sonata");
    return EXIT_FAILURE;
  }
  for (i=0;i<argc;i++)
  {
    printf("%s ",argv[i]);
  }
  puts("");
  return EXIT_SUCCESS;
}
