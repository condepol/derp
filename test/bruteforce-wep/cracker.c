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

  printbuffer(p.data,p.data_length);
  /* create key for 64 bit wep :*/
  memcpy(K,key,5);    /* 40 secret bits */
  memcpy(&K[5],p.iv,3); /* 24 public bits */

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
  crc = crc ^ ~0U;

  /* for each (data||crc) byte */
  for (i=0;i<p.data_length;i++)
  {
    /* decipher byte */
    p.data[i] ^= rc4_byte(&state);
    /* update crc */
    crc = crc32_tab[(crc ^ p.data[i]) & 0xFF] ^ (crc >> 8);
  }
  /* finalize crc */
  crc ^= 0xffffffffU;
  /* compare MCRC and PCRC */
  result = memcmp(p.crc,&crc,4);

  printf("\nCRC %08x == %x%x%x%x\n",crc,p.crc[0],p.crc[1],p.crc[2],p.crc[3]);

  printbuffer(p.data,p.data_length);

  free(state.buffer);
  free(cleartext);
  return result;
}

