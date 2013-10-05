# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include <pthread.h>

# include "wep_utils.c"

# include "rc4.c"
# include "crc32.c"
# include "printers.c"
# include "cracker.c"

# include "../ivs/ivs-known-8.c"

# define NB_THREADS 4
pthread_t thread[NB_THREADS];

# define KEY_SIZE 5

typedef struct {
  unsigned char * key;
  wep_packet packet;
} thread_data;

typedef struct {
  unsigned int nb_keys;
  unsigned char ** keys;
} thread_result;

void * bruteforce (void * input_struct)
{
  unsigned int my_id = 0; 
  thread_result result;
  thread_data data = (thread_data) input_struct;
  wep_packet packet;

  /* get self id */
  for (i = 0; i < NB_THREADS; i++) {
    if (thread[i] == pthread_self()) {
      my_id = i;
    }
  }
  /* set thread cancel type */
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  /* malloc result buffer */
  result.keys = malloc(10*sizeof(unsigned char *));
  for (i=0;i<10;i++) {
    result.keys[i] = malloc(KEY_SIZE);
  }
  result.nb_keys = 0;
  
  tmp_packet = copy_packet(&data.packet);
  
  /* do evil stuff */

  /* check the null key */
  if (check_key(key,tmp_packet))
  {
    /* store key */
    //printf("%s\n",hexa(key,5));
  }
  /* reload data */
  recopy_packet(&packets[0],&tmp_packet);

  /* update only 3 bytes, the 2 others have 65535 different threads (or program instances) */
  while (update_key(key,3)) /* returns 0 at overflow */
  {
    if (check_key(key,tmp_packet))
    {
      /* if needed, realloc */
      if ((result.nb_keys % 10) == 9)
      {
        /* add 10 char **/
        result.keys = realloc(result.keys,result.nb_keys * sizeof(unsigned char *));
        /* for each new char * */
        for (i=result.nb_keys-10;i<result.nb_keys;i++)
        {
          /* malloc 5 chars for each char * */
          result.keys[i] = malloc(KEY_SIZE);
        }
      }
      /* store result (KEY_SIZE bytes) */
      memcpy(result.keys[result.nb_keys],key,KEY_SIZE);
      //printf("%s\n",hexa(key,5));
      result.nb_keys++;
    }
    /* reload chipertext (altered by dechipering tentative) */
    recopy_packet(&packets[0],&tmp_packet);
  }

  free_wep_packet(tmp_packet);

  /* return results */
  return (void *)result;
}


int main(int argc, char * argv[])
{
  unsigned int i = 0;
  unsigned int large_counter = 0;
  wireshark_dico buffers;
  wep_packet * packets = NULL;
  unsigned char * key = NULL;
  wep_packet tmp_packet;
  time_t chrono = 0;
  time_t elapsed = 0;

  key = malloc(5*sizeof(unsigned char));
  memset(key,0,5*sizeof(unsigned char));
  //memcpy(key,(unsigned char *)"\x61\x61\x10\x14\x53",5);
  memcpy(key,(unsigned char *)"\x60\x60\x10\x14\x53",5);
  //memset(key,0,5);


  /* 1. read packets */ 
  buffers = load_packets();
  packets = malloc(buffers.length*sizeof(wep_packet));
  for (i=0;i<buffers.length;i++)
  {
    packets[i] = read_packet(buffers.packets[i].data,buffers.packets[i].length);
  }

  
  tmp_packet = copy_packet(&packets[0]);


  /* 2. parallel : launch threads for each 0x1000000 range (set key = 0x000000XXXX) */
  for (large_counter=0;large_counter<0x10000;large_counter+=NB_THREADS)
  {
    /* prepare memory for the 4 threads */
    // thread_data stuff

    /* launch 4 threads */
    for (i = 0; i < NB_THREADS; i++)
    {
      pthread_create(&thread[i], NULL, bruteforce, &thread_data[i]);
    }


    /* join 4 threads */
    for (i = 0; i < NB_THREADS; i++)
    {
      pthread_join(thread[i], (void **)&result);
      /* read results */
      if (result != -1)
      {
        brute_int = result;
      }
      /* copy results to main results buffer */
    }
  }

  /* 3. validate potential keys with the second packet */

  /* 4. print key */

  /* 5. free memory */
  for (i=0;i<buffers.length;i++)
  {
    free(packets[i].data);
  }
  free(packets);
  free(key);

  /* 6. ??? */
  /* 7. profit !*/
  return EXIT_SUCCESS;
}
