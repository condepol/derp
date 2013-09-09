# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include "crc32.h"

# define NB_THREADS 4

pthread_t thread[NB_THREADS];

void safeprint(unsigned char * data, unsigned int length)
{
  unsigned int i = 0;
  unsigned char c = 0;
  for (i = 0; i < length; i++)
  {
    c = data[i];
    if ((c < 0x20) || (c > 0x7e))
    {
      c = 0x2e;
    }
    printf("%c",c);
  }
}

struct Data
{
  short unsigned int start;
  short unsigned int step;
  unsigned int input;
};

void * bruteforce (void * elder_memory)
{
  /* printf("Coucou c'est %d, fils de %d, fils de %d\n", pthread_self(), getpid(),getppid());*/

  unsigned long long int brute_int = 0;
  unsigned char * brute_string = NULL;
  unsigned int input = 0;
  unsigned int brute_len = 0;
  unsigned short int i = 0;
  unsigned short int j = 0;
  unsigned short int my_id = 0;

  struct Data * data=(struct Data*) elder_memory;
  struct Data mydata = data[0];

  for (i = 0; i < NB_THREADS; i++)
  {
    if (thread[i] == pthread_self())
    {
      my_id = i;
    }
  }

  input = mydata.input;

  brute_int = mydata.start;
  brute_string = malloc(16*sizeof(unsigned char));

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  
  brute_len = sprintf((char *)brute_string,"%llx",brute_int);
  while (input != crc32(0,brute_string,brute_len))
  {
    /*if (brute_int > 1000000)
    {
      printf("Thread %d dying at %lld\n",mydata.start,brute_int);
      return NULL;
    }*/
    brute_len = sprintf((char *)brute_string,"%llx",brute_int);
    brute_int = brute_int + mydata.step;
  }
  
  brute_int = brute_int - mydata.step;
  /* kill others threads */
  
  for (i = 0; i < NB_THREADS; i++)
  {
    if (i != my_id)
    {
      /*printf("Ici thread %d, je vais tuer %d avec un signal %d\n",my_id, (int) thread[i] , 9);*/ /* sigkill */
      /*printf("\n--%d (%d)\n",i, my_id);*/ /* sigkill */
      pthread_cancel((pthread_t) thread[i]); /* sigkill */
      printf("\x1b[5D"); /* back to start of line */
      for (j = 0; j < i; j++)
      {
        printf("\x1b[1C"); /* fetch correct position */
      }
      printf("3");
      fflush(stdout);
    }
  }
  printf("\nI, %d, gently die.\n", my_id); /* sigkill */
  return (void *)brute_int;
}

int main (int argc, char * argv[] )
{
  unsigned long long int brute_int = 47;
  unsigned long long int result = 46;
  struct Data thread_data[NB_THREADS];
  short unsigned int i = 0;
  unsigned int input = 0;
  char *endptr;
  
  /* get word to bruteforce */
  if (argc != 2)
  {
    printf("%s <crc32>",argv[0]);
    return 0;
  }

  input = 0x4e5cdde6;
  input = strtol(argv[1], &endptr, 16);

  printf("Bruteforcing i while crc32(i) != %x\n",input);
  for (i = 0; i < NB_THREADS; i++)
  {
    thread_data[i].start = i;
    thread_data[i].step = NB_THREADS;
    thread_data[i].input = input;
  }

  for (i = 0; i < NB_THREADS; i++)
  {
    pthread_create(&thread[i], NULL, bruteforce, &thread_data[i]);
  }

  for (i = 0; i < NB_THREADS; i++)
  {
    pthread_join(thread[i], (void **)&result);
    if (result != -1)
    {
      brute_int = result;
    }
  }

  printf("crc32('%llx') = %x\n",brute_int,input);
  return 0;
}
