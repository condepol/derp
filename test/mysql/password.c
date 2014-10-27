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
  unsigned int i = 0;
  const char *password_end = password + password_len;
  for (; password < password_end; password++)
  {
    //printf("%2d %08x %08x\n", i++, nr, nr2);
    if (*password == ' ' || *password == '\t')
      continue;                                 /* skip space in password */
    tmp= (unsigned int) (unsigned char) *password;
    nr^= (((nr & 63)+add)*tmp)+ (nr << 8);
    nr2+=(nr2 << 8) ^ nr;
    add+=tmp;
  }
  result[0]=nr & (((unsigned int) 1L << 31) -1L); /* Don't use sign bit (str2int) */;
  result[1]=nr2 & (((unsigned int) 1L << 31) -1L);
}

int main ( int argc, char * argv [] ) {
  unsigned int hash[2] = {0,0};
  if (argc == 1) {
    printf("Usage : %s <password>",argv[0]);
    return EXIT_FAILURE;
  }
  hash_password(hash, argv[1], strlen(argv[1]));
  printf("%08x%08x\n", hash[0], hash[1]);
}
