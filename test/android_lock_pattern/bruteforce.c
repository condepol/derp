# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <openssl/sha.h>

unsigned char input[20];
unsigned char output[20];
unsigned char key[9];

unsigned char nibble(unsigned char x){
  /* it's a lowercase letter */
  if (x > 0x60) {return x - 0x57;}
  /* it's an uppercase letter */
  if (x > 0x40) {return x - 0x37;}
  /* it's a digit */
  return x - 0x30;
}

void recursion(unsigned int level, unsigned int length, unsigned int digit) {
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
      recursion(level-1,length,i);
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
      exit(0);
    }
  }
}

int main(int argc, char * argv []) {
  unsigned int length = 0;
  unsigned int i = 0;

  if ((argc != 2) || (strlen(argv[1]) != 40)) {
    puts("Usage : ./bruteforce <hash> (ex: 2c3422d33fb9dd9cde87657408e48f4e635713cb)");
    return EXIT_FAILURE;
  }

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

  for ( length = 4; length < 10; length++) {
    printf("Length: %d\n",length);
    /* reset key */
    for (i=0;i<length;i++) {
      key[i] = 0;
    }
    /* launch recursion over levels */
    recursion(length,length,0);
  }
  return EXIT_SUCCESS;
}
