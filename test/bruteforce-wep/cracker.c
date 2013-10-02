# define CRC_CORRECT 1
# define CRC_INVALID 0

int check_key(unsigned char * key,wep_packet p)
{
  /* ARC4 Key = ( secret_key || iv_key ) */
  unsigned char K [8];
  /* Computed CRC32 of unciphered data */
  unsigned int crc;
  /* ARC4 internal buffer */
  unsigned char * B = NULL;
  /* index counter */
  unsigned int i = 0;
  /* deciphered data */
  unsigned char * cleartext = NULL;
  /* rc4*/
  rc4_state state = {0,0,NULL};
  /* result */
  unsigned int result;

  //printbuffer(p.data,p.data_length-4);
  /* create key for 64 bit wep :*/
  memcpy(K,p.iv,3);       /* 24 public bits */
  memcpy(&K[3],key,5);    /* 40 secret bits */

  /* allocate memory for deciphered data */
  while (cleartext == NULL)
  {
    cleartext = malloc(p.data_length);
    /* if malloc fails, wait a little*/
    if (cleartext == NULL){sleep(0.2);}
  }






  /* init ARC4 buffer */
  B = init_buffer(K, 8);/* 8 = 64bit wep / sizeof(uchar) */
  state.buffer = B;

  /* init crc */
  crc = 0xffffffffU;

  /* for each (data) byte */
  for (i=0;i<p.data_length-4;i++)
  {
    /* decipher byte */
    p.data[i] ^= rc4_byte(&state);
    /* update crc */
    crc = crc32_tab[(crc ^ p.data[i]) & 0xFF] ^ (crc >> 8);
  }
  /* for each crc byte */
  for (;i<p.data_length;i++)
  {
    /* decipher byte */
    p.data[i] ^= rc4_byte(&state);
  }

  /* finalize crc */
  crc ^= 0xffffffffU;





  /* compare MCRC and PCRC */
  /*
    todo
      - try to compute crc32 with a table that puts bytes in reverse order.
      - cast p.crc to int in order to compare with something like
        ((unsigned int)p.crc) != crc
  */
  if (p.crc[0] == (unsigned char)(crc>>0)) {
    if (p.crc[1] == (unsigned char)(crc>>8)) {
      if (p.crc[2] == (unsigned char)(crc>>16)) {
        if (p.crc[3] == (unsigned char)(crc>>24)) {
          result = CRC_CORRECT;
        } else {result = CRC_INVALID;}
      } else {result = CRC_INVALID;}
    } else {result = CRC_INVALID;}
  } else {result = CRC_INVALID;}

  //result = memcmp(p.crc,&crc,4);





  //printf("\nCRC %08x == %x%x%x%x\n",crc,p.crc[3],p.crc[2],p.crc[1],p.crc[0]);
  //printbuffer(p.data,p.data_length-4);

  free(state.buffer);
  free(cleartext);
  return result;
}



unsigned int update_key(unsigned char * key,unsigned int len)
{
  unsigned int i = 0;
  while (key[i++] == 0xff && i<len) {}
  if (i == len) {return 0;}
  i--;
  while (i+1){key[i--]++;}
  return 1;
}
