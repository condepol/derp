# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <openssl/sha.h>

unsigned char nibble(unsigned char x){
  /* it's a lowercase letter */
  if (x > 0x60) {return x - 0x57;}
  /* it's an uppercase letter */
  if (x > 0x40) {return x - 0x37;}
  /* it's a digit */
  return x - 0x30;
}

void recursion( unsigned int level, unsigned int length, unsigned int digit,
                unsigned char * output,
                unsigned char * input,
                unsigned char * key) {
  unsigned int i;
  /*
  printf("%d %d %d ",level,length,digit);
  for (i=0;i<length;i++) {
    printf("%02x",key[i]);
  }
  putchar('\n');
  */

  key[level] = (unsigned char)digit;
  if (level) {
    for (i=0;i<10;i++) {
      recursion(level-1,length,i,output,input,key);
    }
  } else {
    /* check */
    SHA1(key,length,output);
    if (memcmp(input,output,20) == 0) {
      printf("Key: ");
      for (i=0;i<length;i++) {
        printf("%d",key[i]);
      }
      putchar('\n');
      free(key);
      free(input);
      free(output);
      exit(0);
    }
  }
}

int main(int argc, char * argv []) {
  unsigned int length = 0;
  unsigned int i = 0;
  unsigned char * input;
  unsigned char * output;
  unsigned char * key;

  if ((argc != 2) || (strlen(argv[1]) != 40)) {
    puts("Usage : ./bruteforce <hash> (ex: 2c3422d33fb9dd9cde87657408e48f4e635713cb)");
    return EXIT_FAILURE;
  }

  input   = malloc(20);
  output  = malloc(20);
  key     = malloc(9);

  /* fill input with argv[1] */
  printf("Buffer: ");
  for (i=0;i<40;i++) {
    if (i%2) {
      input [i/2] <<= 4;
      input [i/2] += nibble(argv[1][i]);
      printf("%02x",input[i/2]);
    } else {
      input [i/2] =  nibble(argv[1][i]);
    }
  }
  putchar('\n');

  /* launch recursions */
  for ( length = 4; length < 10; length++) {
    printf("Length: %d\n",length);
    memset(key,0,length);
    recursion(length,length,0,output,input,key);
  }

  free(key);
  free(input);
  free(output);

  return EXIT_SUCCESS;
}
