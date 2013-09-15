# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include "moar_ivs.c"
# include "rc4.c"

# define IV_NUMBER 111

typedef struct {
  unsigned char iv [3];
  unsigned char key_index;
  unsigned char * data;
  unsigned int data_length;
  unsigned char crc [4];
} wep_packet;

typedef struct {
  /* 40 bits = 5 octets */
  unsigned char k[5];
} wep_key;

wep_packet read_packet (const unsigned char * buffer, unsigned int length)
{
  wep_packet output;
  memcpy(output.iv,&buffer[24],3);
  output.key_index = buffer[27]>>6;/* throw the 6 padding bits */
  output.data_length = length-32;
  output.data = malloc(output.data_length);
  memcpy(output.data,&buffer[28],output.data_length);
  memcpy(output.crc,&buffer[length-4],4);
  return output;
}

char * str_packet(wep_packet p)
{
  char * output = NULL;
  /*
  printf("%20s : %d data bytes\n","Wep packet",p.data_length);
  printf("%20s : %02x%02x%02x\n","IV",p.iv[0],p.iv[1],p.iv[2]);
  printf("%20s : %x\n","Key index",p.key_index);
  printf("%20s : %02x%02x%02x%02x\n","CRC",p.crc[0],p.crc[1],p.crc[2],p.crc[3]);
  */
  output = malloc(21);
  sprintf(output,"%02x%02x%02x%2x %3d %02x%02x%02x%02x",p.iv[0],p.iv[1],p.iv[2],p.key_index,p.data_length,p.crc[0],p.crc[1],p.crc[2],p.crc[3]);
  return output;
}

int check_key(wep_key key,wep_packet p)
{
  unsigned char K [8];
  unsigned char mcrc [4];
  unsigned char pcrc [4];
  unsigned char * B = NULL;
  /* create key */
  memcpy(K,key.k,5);
  memcpy(&K[5],p.iv,3);
  /* init ARC4 buffer */
  B = init_buffer(unsigned char * key, 8)/* 8 = 64bit wep / sizeof(uchar) */
  /* decipher data */

  /* decipher p.crc in PCRC */

  /* compute MCRC */

  /* compare MCRC and PCRC */
  return memcmp(pcrc,mcrc,4);
}
int main(int argc, char * argv[])
{
  unsigned int i = 0;
  wep_packet * packets = NULL;
  packets = malloc(IV_NUMBER*sizeof(wep_packet));
  for (i=0;i<IV_NUMBER;i++)
  {
    packets[i] = read_packet(pkts[i],82);
    /*printf("Packet %4d : %s\n",i,str_packet(packets[i]));*/
  }
  return EXIT_SUCCESS;
}
