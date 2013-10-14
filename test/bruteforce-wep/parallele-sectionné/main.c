# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>

# include "wep_utils.c"

# include "rc4.c"
# include "crc32.c"
# include "printers.c"
# include "cracker.c"


# include "../ivs/ivs-known-8.c"
//# include "../ivs/ivs-unknown-9.c"

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

unsigned int large_counter = 0;

void my_handler(int s){
  if (s==2) {
    printf("\nStopped at xxxxxx:%04x\n",large_counter);
    exit(EXIT_SUCCESS); 
  } else {
    printf("Caught signal %d\n",s);
    exit(EXIT_FAILURE); 
  }
}

void * bruteforce (void * input_struct)
{
  //unsigned int my_id = 0;
  unsigned int i = 0;
  thread_result * result;
  thread_data * vdata;
  thread_data data;
  wep_packet packet;
  unsigned char * key;

  vdata = (thread_data *)(input_struct);
  data = vdata[0];
   

  /* set thread cancel type */
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);


  /* malloc result buffer */
  result = malloc(sizeof(thread_result));
  result->keys = malloc(10*sizeof(unsigned char *));
  for (i=0;i<10;i++) {
    result->keys[i] = malloc(KEY_SIZE);
  }
  result->nb_keys = 0;
  
  packet = copy_packet(&data.packet);
  key = malloc(KEY_SIZE);
  if (key==NULL) {
    sleep(0.01);
    //puts("Failed to malloc !");
    key = malloc(KEY_SIZE);
  }
  memcpy(key,data.key,KEY_SIZE);
  

  /* check the null key */
  if (check_key(key,packet))
  {
    /* store key */
    /* if needed, realloc */
    if ((result->nb_keys % 10) == 9)
    {
      /* add 10 char **/
      result->keys = realloc(result->keys,result->nb_keys * sizeof(unsigned char *));
      /* for each new char * */
      for (i=result->nb_keys-10;i<result->nb_keys;i++)
      {
        /* malloc 5 chars for each char * */
        result->keys[i] = malloc(KEY_SIZE);
      }
    }
    /* store result (KEY_SIZE bytes) */
    memcpy(result->keys[result->nb_keys],key,KEY_SIZE);
    //printf("%s\n",hexa(key,5));
    result->nb_keys++;
  }
  /* reload data */
  recopy_packet(&data.packet,&packet);

  i = 0;
  /* update only 3 bytes, the 2 others have 65535 different threads (or program instances) */
  while (update_key(key,4)) /* returns 0 at overflow */
  {
    i++;
    if (check_key(key,packet))
    {
      /* if needed, realloc */
      if ((result->nb_keys % 10) == 9)
      {
        /* add 10 char **/
        result->keys = realloc(result->keys,result->nb_keys * sizeof(unsigned char *));
        /* for each new char * */
        for (i=result->nb_keys-10;i<result->nb_keys;i++)
        {
          /* malloc 5 chars for each char * */
          result->keys[i] = malloc(KEY_SIZE);
        }
      }
      /* store result (KEY_SIZE bytes) */
      memcpy(result->keys[result->nb_keys],key,KEY_SIZE);
      //printf("%s\n",hexa(key,5));
      result->nb_keys++;
    }
    /* reload chipertext (altered by dechipering tentative) */
    recopy_packet(&data.packet,&packet);
  }

  free_wep_packet(&packet);

  //printf("thread %d will return %d keys from %d tries\n",(unsigned int)pthread_self(),result->nb_keys,i);
  /* return results */
  pthread_exit((void **)result);
  return      ((void **)result);
}


int main(int argc, char * argv[])
{
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;
  wireshark_dico buffers;
  wep_packet * packets = NULL;
  wep_packet tmp_packet;
  wep_packet check_packet;
  wep_packet check_packet_fixed;
  thread_data * packed_data = NULL;
  thread_result * result;
  unsigned int init_section = 0;
  unsigned int last_section = 0;

  time_t timer;
  time_t diff;
  struct sigaction sigIntHandler;

  //key = malloc(KEY_SIZE*sizeof(unsigned char));
  //memset(key,0,KEY_SIZE*sizeof(unsigned char));
  //memcpy(key,(unsigned char *)"\x61\x61\x10\x14\x53",5);
  //memcpy(key,(unsigned char *)"\x60\x60\x10\x14\x53",KEY_SIZE);
  //memset(key,0,5);

  sigIntHandler.sa_handler = my_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);



  packed_data = malloc(NB_THREADS * sizeof(thread_data));

  /* 1. read packets */ 
  buffers = load_packets();
  packets = malloc(buffers.length*sizeof(wep_packet));
  for (i=0;i<buffers.length;i++)
  {
    packets[i] = read_packet(buffers.packets[i].data,buffers.packets[i].length);
  }

  // use the first packet
  tmp_packet = copy_packet(&packets[0]);
  check_packet_fixed = copy_packet(&packets[1]);
  check_packet = copy_packet(&check_packet_fixed);


  /* read param */
  if ( argc == 1)
  {
    printf("%s <0xinit> [0xlast]  (section = 0x??????derp)\n",argv[0]);
    return EXIT_SUCCESS;
  } else {
    init_section = strtol(argv[1],NULL,16);
    if (argc == 3)
    {
      last_section = strtol(argv[2],NULL,16);
    } else {
      last_section = 0x10000;
    }
  }
  
  time(&timer);
  printf("Started on %s",ctime(&timer));
  printf("xx:xx:xx:%02x:%02x -> xx:xx:xx:%02x:%02x\n",init_section >> 8,init_section % 0x100,last_section >> 8,last_section % 0x100);

  /* 2. parallel : launch threads for each 0x1000000 range (set key = 0x000000XXXX) */
  for (large_counter=init_section;large_counter<last_section;large_counter+=NB_THREADS)
  {
    diff = timer;
    /* prepare memory for the 4 threads */
    // thread_data stuff
    for (i=0; i < NB_THREADS; i++)
    {
      packed_data[i].packet = copy_packet(&tmp_packet);
      packed_data[i].key = malloc(KEY_SIZE);
      memset(packed_data[i].key,0,KEY_SIZE);
      //packed_data[i].key[2] = 0x10; // YOLO YOLO
      packed_data[i].key[KEY_SIZE-2] = large_counter >> 8;
      packed_data[i].key[KEY_SIZE-1] = (large_counter + i)% 0x100;
    }    

    //printf("\x1b[32mNew wave !\x1b[0m %02x%02x%02x%02x%02x\n",packed_data[0].key[0],packed_data[0].key[1],packed_data[0].key[2],packed_data[0].key[3],packed_data[0].key[4]);
    printf("xx:xx:xx:%02x:%02x\n",packed_data[0].key[3],packed_data[0].key[4]);
    /* launch 4 threads */
    for (i = 0; i < NB_THREADS; i++)
    {
      pthread_create(&thread[i], NULL, bruteforce, &packed_data[i]);
    }


    /* join 4 threads */
    for (i = 0; i < NB_THREADS; i++)
    {
      pthread_join(thread[i], (void **)&result);
      /* read results */
      if (result->nb_keys != 0)
      {
        // printf("thread %d returned %d keys\n",i,result->nb_keys);
        for (j=0;j<result->nb_keys;j++)
        {
          //printf("potential key : ");

          /* 3. validate potential keys with the second packet */
          // copy packet
          recopy_packet(&check_packet_fixed,&check_packet);

          // check key
          if (check_key(result->keys[j],check_packet))
          {
            // Yay !
            printf("Yay ! ");
            for (k=0;k<KEY_SIZE;k++)
            {
              printf("%02x",result->keys[j][k]);
              if (k<KEY_SIZE-1) {
                printf(":");
              }
            }
            printf("\n");           
            //printf("%s\n",hexa(key,5));
          }
          /* reload data */
    
        }
      }
    }
    time(&timer);
    printf("Bruteforced %d sections in %.0fs.\n",NB_THREADS,difftime(timer,diff));
    printf("Remaining : %.0fs.\n",difftime(timer,diff)*((float)(0x10000-large_counter) /NB_THREADS));
  }


  /* 5. free memory */
  for (i=0;i<buffers.length;i++)
  {
    free(packets[i].data);
  }
  free(packets);
  //free(key);

  /* 6. ??? */
  /* 7. profit !*/
  return EXIT_SUCCESS;
}
