# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct {
  unsigned char iv [3];
  unsigned char key_index;
  unsigned char * data;
  unsigned int data_length;
  unsigned char * crc;
} wep_packet;

# include "rc4.c"
# include "crc32.c"
# include "printers.c"
# include "reader.c"
# include "cracker.c"
# include "ivs_2.c"
//# include "yolo.c"

int main(int argc, char * argv[])
{
  unsigned int i = 0;
  wireshark_dico buffers;
  wep_packet * packets = NULL;
  unsigned char * key = NULL;

  key = malloc(5*sizeof(unsigned char));
  memset(key,0,5*sizeof(unsigned char));
  memcpy(key,(unsigned char *)"\x61\x61\x10\x14\x53",5);


  /* 1. read packets */ 
  buffers = load_packets();
  packets = malloc(buffers.length*sizeof(wep_packet));
  for (i=0;i<buffers.length;i++)
  {
    packets[i] = read_packet(buffers.packets[i].data,buffers.packets[i].length);
  }

  /* 2. try keys */
  for (i=0;i<buffers.length;i++)
  {
    print_packet(packets[i]);
    printf("Packet %d, key %s : %d\n",i,hexa(key,5),check_key(key,packets[i]));
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
