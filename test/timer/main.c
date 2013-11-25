# include <time.h>
# include <stdio.h>
# include <stdlib.h>

# include "timer.c"
int main(int argc, char * argv[])
{
  unsigned int seconde = 0;
  unsigned int i = 0;
  unsigned int d = 0;
  unsigned int z = 0;
  time_t * sec = 0;

  struct time_log * record;

  sec = malloc(sizeof(time_t));
  record = malloc(sizeof(struct time_log));

  init_time_log(record);
  time(sec);

  log_time(record,"Initialisation");

  printf("%s",ctime(sec));
  while (difftime(time(NULL),*sec) < 1) {  
    seconde++;
  }
  log_time(record,"fin du calcul");
  time(sec);
  printf("%s",ctime(sec));
  printf("seconds = %d s\n",seconde);
  for (d=1;d<0x80;d++) {
    log_time(record,"itération");
    for (i=0;i<(seconde/d);i++) {
      z++;
    }
    printf("%2x ",d);
    fflush(stdout);
  }
  puts("");
  log_time(record,"fin");
  print_times(record);
  free(sec);
  free_time_log(record);
  free(record);
}
