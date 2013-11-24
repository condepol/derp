# include <stdio.h>
# include <stdlib.h>

# include "meta-gf256.c"

int main()
{
  unsigned char * gflog = NULL;
  unsigned char * gfilog = NULL;
  unsigned int i = 0;

  gflog = malloc(0x100);
  gfilog = malloc(0x100);

  setup_tables(gflog,gfilog);

  printf("# ifndef __GF256__\n# define __GF256__\n");
  printf("# include <stdio.h>\n# include <stdlib.h>\n# include <string.h>\n# include <assert.h>\n");
  printf("const unsigned char gflog[256] = {");
  for (i=0;i<0x100;i++) {if ((i%0x10) == 0) {printf("\n  ");} printf("0x%02x, ",gflog[i]);}
  printf("};\nconst unsigned char gfilog[256] = {");
  for (i=0;i<0x100;i++) {if ((i%0x10) == 0) {printf("\n  ");} printf("0x%02x, ",gfilog[i]);}
  printf("};\n");

  printf("unsigned char gf_mul(unsigned char a,unsigned char b)\n{\n  if (a==0||b==0) return 0;\n  return (unsigned char)gfilog[(unsigned char)(gflog[a] + gflog[b])];\n}\n\nunsigned char gf_div(unsigned char a,unsigned char b)\n{\n  assert(b != 0);\n  if (a==0) return 0;\n  return gfilog[(unsigned char)(gflog[a]-gflog[b])];\n}\nunsigned char gf_pow(unsigned char a,unsigned char b)\n{\n  unsigned char result = 0x01;\n  while (b--) {\n    result = gf_mul(result,a);\n  }\n  return result;\n}\n# endif");
  free(gflog);
  free(gfilog);
}
/*
unsigned char gf_pow(unsigned char a,unsigned char b)
{
  unsigned int i = 0;
  unsigned char result = 0x01;
  while (b--) {
    result = gf_mul(result,a);
  }
  return result;
}
*/
