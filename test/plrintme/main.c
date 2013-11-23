# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


int main(int argc, char * argv[])
{
  ssize_t n = 1;
  int fd;
  unsigned char buffer[512];
  fd = open(argv[0],O_RDONLY);
  n = read(fd,buffer,512);
  while (n)
  {
    write(STDOUT_FILENO,buffer,n);
    n = read(fd,buffer,512);
  }
  return 0;
}
