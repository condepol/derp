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

unsigned char * rc4_bytes(unsigned char * S, unsigned int n)
{
  unsigned char i = 0;
  unsigned char j = 0;
  unsigned char tmp = 0;
  unsigned char * output = NULL;
  unsigned int counter = 0;

  output = malloc(n*sizeof(unsigned char));

  while (n-counter++)
  {
    i++;
    j+=S[i];
    /* swap */
    tmp = S[i]; S[i] = S[j];S[j] = tmp;
    output[counter] = S[(S[i]+S[j])];
  }
  return output;
}
