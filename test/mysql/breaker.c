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

void hash_password(unsigned int *result, const char *password, unsigned int password_len)
{
  register unsigned int nr=1345345333L, add=7, nr2=0x12345671L;
  unsigned int tmp;
  const char *password_end= password + password_len;
  for (; password < password_end; password++)
  {
    if (*password == ' ' || *password == '\t')
      continue;                                 /* skip space in password */
    tmp= (unsigned int) (char) *password;
    nr^= (((nr & 63)+add)*tmp)+ (nr << 8);
    nr2+=(nr2 << 8) ^ nr;
    add+=tmp;
  }
  result[0]=nr & (((unsigned int) 1L << 31) -1L); /* Don't use sign bit (str2int) */;
  result[1]=nr2 & (((unsigned int) 1L << 31) -1L);
}

void bruteforce(char * buffer, unsigned int len, unsigned int step, char * charset, unsigned int charlen, unsigned int * known) {
  char * charc = charset + charlen;
  if (step == len) {
    unsigned int our[2] = {0,0};
    hash_password(our,buffer,len);
    if ((our[0] == known[0]) & (our[1] == known[1])) {
      printf("%s",buffer);
    }
  } else {
    do {
      buffer[step] = *charc;
      bruteforce(buffer,len,step+1,charset,charlen,known);
    }
    while (charc-- != charset);
  }
}

int main ( int argc, char * argv [] ) {
  unsigned int hash[2];
  char tested[40];
  char tmp[9];
  unsigned int tested_length;
  char charset[94] = {'!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','|','}','~'};

  if (argc == 1) {
    printf("Usage : %s hash length [charset]",argv[0]);
    return EXIT_FAILURE;
  }
 

  memset(tested,0,40);
  memset(tmp,0,9);
  memcpy(tmp,argv[1],8);
  hash[0] = strtol(tmp,NULL,16);
  memset(tmp,0,9);
  memcpy(tmp,argv[1]+8,8);
  hash[1] = strtol(tmp,NULL,16);

  tested_length = atoi(argv[2]);
  printf("%08x%08x:",hash[0],hash[1]);
  if (argc == 3) {
    bruteforce(tested,tested_length,0,charset,94,hash);
  } else {
    bruteforce(tested,tested_length,0,argv[3],strlen(argv[3]),hash);
  }
  printf("\n");
  return EXIT_SUCCESS;
}
