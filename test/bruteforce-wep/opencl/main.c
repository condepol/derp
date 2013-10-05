# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include "wep_utils.c"

# include "rc4.c"
# include "crc32.c"
# include "printers.c"
# include "cracker.c"

# include "../ivs/ivs-known-8.c"

int main(int argc, char * argv[])
{
  unsigned int i = 0;
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

  //for (i=0;i<buffers.length;i++)
  //{

  //  // iterative version
  //  tmp_packet = copy_packet(&packets[i]);
  //  //print_packet(tmp_packet);
  //  printf("Packet %d, key %s : %d\n",i,hexa(key,5),check_key(key,tmp_packet));
  //  free_wep_packet(&tmp_packet);
  //}

  /* 2. iterative : bruteforce keys */
  printf("Initial key : %s\n",hexa(key,5));
  tmp_packet = copy_packet(&packets[0]);

  /* check the null key */
  if (check_key(key,tmp_packet)){printf("%s (yolo null key)\n",hexa(key,5));}
  /* reload data */
  recopy_packet(&packets[0],&tmp_packet);

  chrono = time(NULL);

  while (update_key(key,5)) /* returns 0 at overflow */
  {
    if (key[1] == 0x00 && key[0] == 0x00) {
      elapsed = time(NULL) - chrono;
      printf("%ds %s\n",(int)(elapsed),hexa(key,5));
    }
    if (check_key(key,tmp_packet))
    {
      printf("%s\n",hexa(key,5));
    }
    recopy_packet(&packets[0],&tmp_packet);
  }

  /* 3. free memory */
  for (i=0;i<buffers.length;i++)
  {
    free(packets[i].data);
  }
  free(packets);
  free(key);


  return EXIT_SUCCESS;
}
