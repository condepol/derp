# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>

unsigned int length;
char ** buffer_stack;

void recursion(char * charset, unsigned int charset_length,unsigned int level)
{
  unsigned int i = 0;
  unsigned int bi = 0;

  if (level)
  {
    for (i=0;i<charset_length;i++)
    {
      for (bi=length-level;bi<length;bi++) {
        buffer_stack[bi][length-level] = charset[i];
      }
      recursion(charset,charset_length,level-1);
    }
  } else {
    for (i=0;i<length;i++) {putchar(buffer_stack[length-1][i]);}
    putchar('\n');
  }
}

typedef struct {
  char * name;
  char * charset;
  unsigned int charset_length;
} known_charset;

# define KNOWN_CHARSETS 9
known_charset dico [] = {
  {"ascii"," !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",95},
  {"digits","0123456789",10},
  {"letters","azertyuiopqsdfghjklmwxcvbn",26},
  {"LETTERS","AZERTYUIOPQSDFGHJKLMWXCVBN",26},
  {"Letters","azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN",52},
  {"hexa","0123456789abcdef",16},
  {"HEXA","0123456789ABCDEF",16},
  {"symbols"," !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",34},
  {"full","\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff",0x100}
};

int match_known_charset(char * name,unsigned int * charset_length, char ** charset)
{
  unsigned int i = 0;
  for (i=0;i<KNOWN_CHARSETS; i++)
  {
    if (strcmp(dico[i].name,name) == 0)
    {
      *charset = dico[i].charset;
      *charset_length = dico[i].charset_length;
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

/* safe printing function */
void safe(char * input,unsigned int length)
{
  unsigned int i;
  for (i=0;i<length;i++)
  { 
    if (isgraph(input[i]))
    {
      printf("%c",input[i]);
    } else {
      printf(".");
    }
  }
}

int main (int argc, char * argv[])
{
  char * charset = NULL;
  unsigned int used_user_charset = 0;
  unsigned int charset_length;
  unsigned int start_level;
  unsigned int i;

  /* read arguments */
  if ((argc < 3 )||(argc > 4))
  {
    printf("Usage : %s <charset> <length> [prefix]\n",argv[0]);
    puts("Charsets :");
    for (length=0;length<KNOWN_CHARSETS;length++)
    {
      printf("%10s «",dico[length].name);
      safe(dico[length].charset,dico[length].charset_length);
      printf("»\n");
    }
    return EXIT_FAILURE;
  }

  /* identify charset */
  if (match_known_charset(argv[1],&charset_length,&charset) == EXIT_FAILURE)
  {
    /* if not known, allocate and copy user defined. */
    charset_length = strlen(argv[1]);
    charset = malloc(charset_length);
    strncpy(charset,argv[1],charset_length);
    used_user_charset = 1;
  }

  /* get desired length */
  length = atoi(argv[2]);
  
  /* allocate memory */
  buffer_stack = malloc(length * sizeof(char *));
  if (buffer_stack == NULL) {
    printf("bro are u srs ?");
    if (used_user_charset) {free(charset);}
    return EXIT_FAILURE;
  }
  for (i=0;i<length;i++) {
    buffer_stack[i] = malloc(length * sizeof(char));
    if (buffer_stack[i] == NULL) {
      sleep(0.2);
      buffer_stack[i] = malloc(length * sizeof(char));
      if (buffer_stack[i] == NULL) {
        printf("Two mallocs of %d bytes failed, fix you system.\n",length);
        /* nique les fuites */
        return EXIT_FAILURE;
      }
    }
    memset(buffer_stack[i],66,length);
  }

  /* check prefix existence */
  if (argc == 4)
  {
    if (strlen(argv[3]) > length)
    {
      fprintf(stderr,"prefix too long\n");
      /* be nice, free memory. */
      for (i=0;i<length;i++) {free(buffer_stack[i]);}
      free(buffer_stack);
      if (used_user_charset) {free(charset);}
      return EXIT_FAILURE;
    }
    for (i=0;i<length;i++) {strcpy(buffer_stack[i],argv[3]);}
    start_level = length-strlen(argv[3]);
  } else {
    start_level = length;
  }


  /* do stuff */
  recursion(charset,charset_length,start_level);


  /* free allocated memory */
  for (i=0;i<length;i++) {
    free(buffer_stack[i]);
  }
  free(buffer_stack);

  /* only if we used user charset */
  if (used_user_charset) {free(charset);}

  return EXIT_SUCCESS;
}
