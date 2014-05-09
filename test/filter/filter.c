# include <stdio.h>
# include <string.h>
# include <stdlib.h>

unsigned char hexa(unsigned char x){
  if (x < 0x3a) {
    /* digit */
    return x % 0x30;
  } else {
    /* letter
    40 @ A B C D E F G H I J K L M N O
    50 P Q R S T U V W X Y Z [ \ ] ^ _
    60 ` a b c d e f g h i j k l m n o
    70 p q r s t u v w x y z { | } ~ .
    */
    return (x % 0x20)+9;
  }
}

int main(int argc, char * argv[]) {
  int fd = 0;
  unsigned char buffer[1024];
  unsigned char unwanted[256];
  unsigned int unwanted_number = 0;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int length = 0;
  unsigned int okay = 0;

  /* ./prog <unwanted bytes> [filename] */
  if (argc == 1) {
    printf("./prog <unwanted bytes> [filename]\n");
    return EXIT_SUCCESS;
  }

  unwanted_number = strlen(argv[1]);
  if (unwanted_number & 1) {
    printf("Unwanted bytes should be in hexa, thus an even number of letters is needed.\n");
    return EXIT_SUCCESS;
  }
  unwanted_number >>= 1;
  for (i=0;i<unwanted_number;i++){
    unwanted[i] = (hexa(argv[1][2*i]) << 4) + hexa(argv[1][(2*i)+1]);
    printf("Unwanted %d : %02x\n",i,unwanted[i]);
  }

  if (argc>2) {fd = open(argv[2],0x72);}

  memset(buffer,0,1024);

  while ((length = read((int)fd,buffer,1024)) > 0) {
    for (i=0;i<length;i++) {
      okay = 1;
      for (j=0;j<unwanted_number;j++) {
        if (unwanted[j] == buffer[i]) {
          okay = 0;
        }
      }
      if (okay) {
        putchar(buffer[i]);
      }
    }
  }

  return EXIT_SUCCESS;
}
