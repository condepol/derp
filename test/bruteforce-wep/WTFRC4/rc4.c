typedef struct {
  unsigned char i;
  unsigned char j;
  unsigned char * buffer;
} rc4_state;

unsigned char * init_buffer(unsigned char * key, unsigned int keylen)
{
  unsigned char * S = NULL;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int swap = 0;
  S = malloc(sizeof(unsigned char)*256);
  for (i=0;i<256;i++) {S[i]=i;}
  for (i=0;i<256;i++)
  {
    j = (j + S[i] + key[i%keylen]) % 256;
    swap = S[i];
    S[i] = S[j];
    S[j] = swap;
  }
  return S;
}

unsigned char rc4_byte(rc4_state * state)
{
  unsigned char tmp;
  state->i++;
  state->j += state->buffer[state->i];
  tmp = state->buffer[state->i ] ;
  state->buffer [ state->i ]  = state->buffer [ state->j ] ;
  state->buffer [ state->j ]  = tmp;
  return state->buffer [ (state->buffer [ state->i ] +state->buffer [ state->j ] ) ] ;
}
