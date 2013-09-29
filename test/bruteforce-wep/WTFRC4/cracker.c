void check_key(unsigned char * key)
{
  /* ARC4 Key = ( secret_key || iv_key ) */
  unsigned char K [8];
  /* ARC4 internal buffer */
  unsigned char * B = NULL;
  /* index counter */
  unsigned int i = 0;
  /* rc4*/
  rc4_state * state = NULL;
  state = malloc(sizeof(rc4_state));
  state->i = 0;
  state->j = 0;
  
  /* init ARC4 buffer */
  memcpy(K,key,8);
  B = init_buffer(K, 8);/* 8 = 64bit wep / sizeof(uchar) */
  state->buffer = B;

  for (i=0;i<512;i++){printf("%c",rc4_byte(state));}
  free(B);
}
