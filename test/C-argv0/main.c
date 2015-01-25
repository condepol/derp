# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>



int main(int argc, char * argv[])
{
  char * string = NULL;
  unsigned int i = 0;
  unsigned char secret[5] = "YOLO\n";

  if (argc < 3)
  {
    printf(argv[0]);
    return EXIT_FAILURE;
  } else {
    printf(argv[0]);
    printf(argv[1]);
    printf(argv[2]);
  }
  return EXIT_SUCCESS;
}
