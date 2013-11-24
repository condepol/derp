# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

unsigned int polynome = 0x11d;

void setup_tables (unsigned char * gflog,unsigned char * gfilog)
{
  unsigned int b = 1;
  unsigned int log = 0;

  memset(gflog,0,0x100);
  memset(gfilog,0,0x100);

  for (log = 0;log < 0x100; log++)
  {
    gflog[b] = (unsigned char) log;
    gfilog[log] = (unsigned char) b;
    b = b << 1;
    if (b & 0x100) {b ^= polynome;}
  }

  gflog[1] = 0x00;
}

unsigned char gf_mul(unsigned char a,unsigned char b,unsigned char * gflog,unsigned char * gfilog)
{
  if (a==0||b==0) return 0;
  return (unsigned char)gfilog[(unsigned char)(gflog[a] + gflog[b])];
}

unsigned char gf_div(unsigned char a,unsigned char b,unsigned char * gflog,unsigned char * gfilog)
{
  assert(b != 0);
  if (a==0) return 0;
  return gfilog[(unsigned char)(gflog[a]-gflog[b])];
}
