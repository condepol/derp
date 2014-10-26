# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

/*
   from mysql source code, see their gplv2 license.

   Generate binary hash from raw text string 
   Used for Pre-4.1 password handling
   SYNOPSIS
   hash_password()
   result       OUT store hash in this location
   password     IN  plain text password to build hash
   password_len IN  password length (password may be not null-terminated)
 */

void hash_password(unsigned int *result, const unsigned char *password, unsigned int password_len)
{
  register unsigned int nr=1345345333L, add=7, nr2=0x12345671L;
  unsigned int tmp;
  const unsigned char *password_end= password + password_len;
  for (; password < password_end; password++)
  {
    tmp= (unsigned int) (unsigned char) *password;
    nr^= (((nr & 63)+add)*tmp)+ (nr << 8);
    nr2+=(nr2 << 8) ^ nr;
    add+=tmp;
  }
  result[0]=nr & (((unsigned int) 1L << 31) -1L); /* Don't use sign bit (str2int) */;
  result[1]=nr2 & (((unsigned int) 1L << 31) -1L);
}

void bruteforce(unsigned int * profile, unsigned char * buffer, unsigned int len, unsigned int step, unsigned char * charset, unsigned int charlen) {
  unsigned char * charc = charset + charlen;
  unsigned int our[2] = {0,0};
  unsigned int i = 0;
  if (step == len) {
    /* the buffer is in the final state, we have to hash and store*/
    hash_password(our,buffer,len);
    for (i=0;i<32;i++) {
      profile[i]    += (our[0] >> (31-i))&1;
      profile[i+32] += (our[1] >> (31-i))&1;
    }
  } else {
    do {
      buffer[step] = *charc;
      bruteforce(profile,buffer,len,step+1,charset,charlen);
    }
    while (charc-- != charset);
  }
}

int main ( int argc, char * argv [] ) {
  unsigned char tested[40];
  unsigned int profile[64];
  unsigned int tested_length;
  unsigned int i = 0;
  unsigned char charset[256];
  unsigned int test[2];
  unsigned char * passtest = "whatthehell\xea\x8a\x80\xf0\x90\x8c\x88\xdc\x97\xea\xa2\x8b";

  if (argc == 1) {
    printf("Usage : %s length [charset]",argv[0]);
    return EXIT_FAILURE;
  }

  hash_password(test,passtest,strlen(passtest));
  printf("%s : %08x%08x\n",passtest,test[0],test[1]);
    
  memset(profile,0,64*sizeof(unsigned int));
  for (i=0;i<256;i++) {charset[i] = (unsigned char)i;}
  tested_length = atoi(argv[1]);
  if (argc == 2) {
    bruteforce(profile,tested,tested_length,0,charset,255);
  } else {
    bruteforce(profile,tested,tested_length,0,(unsigned char *)argv[2],strlen(argv[2]));
  }
  for (i=0;i<32;i++) {printf("%3x ",profile[i]);}printf("\n");
  for (i=32;i<64;i++) {printf("%3x ",profile[i]);}printf("\n");
  return EXIT_SUCCESS;
}
