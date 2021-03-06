# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

# define MAX_ITERATIONS 10000

unsigned char color[256][3] = {
  {0xff,0x00,0x00},{0xff,0x06,0x00},{0xff,0x0c,0x00},{0xff,0x11,0x00},{0xff,0x18,0x00},{0xff,0x1e,0x00},{0xff,0x23,0x00},{0xff,0x29,0x00},
  {0xff,0x30,0x00},{0xff,0x36,0x00},{0xff,0x3c,0x00},{0xff,0x41,0x00},{0xff,0x48,0x00},{0xff,0x4e,0x00},{0xff,0x53,0x00},{0xff,0x59,0x00},
  {0xff,0x60,0x00},{0xff,0x66,0x00},{0xff,0x6c,0x00},{0xff,0x71,0x00},{0xff,0x78,0x00},{0xff,0x7e,0x00},{0xff,0x83,0x00},{0xff,0x8a,0x00},
  {0xff,0x90,0x00},{0xff,0x96,0x00},{0xff,0x9c,0x00},{0xff,0xa2,0x00},{0xff,0xa8,0x00},{0xff,0xae,0x00},{0xff,0xb3,0x00},{0xff,0xba,0x00},
  {0xff,0xc0,0x00},{0xff,0xc6,0x00},{0xff,0xcc,0x00},{0xff,0xd2,0x00},{0xff,0xd8,0x00},{0xff,0xde,0x00},{0xff,0xe3,0x00},{0xff,0xea,0x00},
  {0xff,0xf0,0x00},{0xff,0xf6,0x00},{0xff,0xfc,0x00},{0xfc,0xff,0x00},{0xf6,0xff,0x00},{0xf0,0xff,0x00},{0xea,0xff,0x00},{0xe3,0xff,0x00},
  {0xde,0xff,0x00},{0xd7,0xff,0x00},{0xd2,0xff,0x00},{0xcb,0xff,0x00},{0xc5,0xff,0x00},{0xc0,0xff,0x00},{0xba,0xff,0x00},{0xb3,0xff,0x00},
  {0xae,0xff,0x00},{0xa7,0xff,0x00},{0xa2,0xff,0x00},{0x9c,0xff,0x00},{0x96,0xff,0x00},{0x90,0xff,0x00},{0x8a,0xff,0x00},{0x83,0xff,0x00},
  {0x7e,0xff,0x00},{0x78,0xff,0x00},{0x71,0xff,0x00},{0x6b,0xff,0x00},{0x65,0xff,0x00},{0x60,0xff,0x00},{0x59,0xff,0x00},{0x53,0xff,0x00},
  {0x4e,0xff,0x00},{0x48,0xff,0x00},{0x41,0xff,0x00},{0x3c,0xff,0x00},{0x36,0xff,0x00},{0x30,0xff,0x00},{0x29,0xff,0x00},{0x23,0xff,0x00},
  {0x1e,0xff,0x00},{0x18,0xff,0x00},{0x11,0xff,0x00},{0x0b,0xff,0x00},{0x05,0xff,0x00},{0x00,0xff,0x00},{0x00,0xff,0x05},{0x00,0xff,0x0b},
  {0x00,0xff,0x11},{0x00,0xff,0x17},{0x00,0xff,0x1e},{0x00,0xff,0x23},{0x00,0xff,0x29},{0x00,0xff,0x2f},{0x00,0xff,0x36},{0x00,0xff,0x3c},
  {0x00,0xff,0x41},{0x00,0xff,0x47},{0x00,0xff,0x4e},{0x00,0xff,0x54},{0x00,0xff,0x5a},{0x00,0xff,0x60},{0x00,0xff,0x66},{0x00,0xff,0x6c},
  {0x00,0xff,0x72},{0x00,0xff,0x78},{0x00,0xff,0x7e},{0x00,0xff,0x83},{0x00,0xff,0x89},{0x00,0xff,0x8f},{0x00,0xff,0x96},{0x00,0xff,0x9c},
  {0x00,0xff,0xa2},{0x00,0xff,0xa7},{0x00,0xff,0xae},{0x00,0xff,0xb4},{0x00,0xff,0xba},{0x00,0xff,0xc0},{0x00,0xff,0xc5},{0x00,0xff,0xcb},
  {0x00,0xff,0xd1},{0x00,0xff,0xd7},{0x00,0xff,0xde},{0x00,0xff,0xe3},{0x00,0xff,0xe9},{0x00,0xff,0xef},{0x00,0xff,0xf6},{0x00,0xff,0xfc},
  {0x00,0xfc,0xff},{0x00,0xf6,0xff},{0x00,0xf0,0xff},{0x00,0xea,0xff},{0x00,0xe3,0xff},{0x00,0xdd,0xff},{0x00,0xd7,0xff},{0x00,0xd1,0xff},
  {0x00,0xcb,0xff},{0x00,0xc5,0xff},{0x00,0xc0,0xff},{0x00,0xba,0xff},{0x00,0xb3,0xff},{0x00,0xad,0xff},{0x00,0xa7,0xff},{0x00,0xa2,0xff},
  {0x00,0x9c,0xff},{0x00,0x96,0xff},{0x00,0x90,0xff},{0x00,0x8a,0xff},{0x00,0x83,0xff},{0x00,0x7e,0xff},{0x00,0x78,0xff},{0x00,0x72,0xff},
  {0x00,0x6c,0xff},{0x00,0x66,0xff},{0x00,0x60,0xff},{0x00,0x5a,0xff},{0x00,0x53,0xff},{0x00,0x4d,0xff},{0x00,0x47,0xff},{0x00,0x41,0xff},
  {0x00,0x3c,0xff},{0x00,0x36,0xff},{0x00,0x30,0xff},{0x00,0x2a,0xff},{0x00,0x23,0xff},{0x00,0x1d,0xff},{0x00,0x17,0xff},{0x00,0x11,0xff},
  {0x00,0x0b,0xff},{0x00,0x05,0xff},{0x00,0x00,0xff},{0x05,0x00,0xff},{0x0b,0x00,0xff},{0x11,0x00,0xff},{0x17,0x00,0xff},{0x1d,0x00,0xff},
  {0x23,0x00,0xff},{0x29,0x00,0xff},{0x2f,0x00,0xff},{0x35,0x00,0xff},{0x3c,0x00,0xff},{0x41,0x00,0xff},{0x47,0x00,0xff},{0x4d,0x00,0xff},
  {0x53,0x00,0xff},{0x59,0x00,0xff},{0x5f,0x00,0xff},{0x65,0x00,0xff},{0x6c,0x00,0xff},{0x72,0x00,0xff},{0x78,0x00,0xff},{0x7e,0x00,0xff},
  {0x83,0x00,0xff},{0x89,0x00,0xff},{0x8f,0x00,0xff},{0x95,0x00,0xff},{0x9c,0x00,0xff},{0xa2,0x00,0xff},{0xa8,0x00,0xff},{0xae,0x00,0xff},
  {0xb4,0x00,0xff},{0xba,0x00,0xff},{0xc0,0x00,0xff},{0xc5,0x00,0xff},{0xcc,0x00,0xff},{0xd2,0x00,0xff},{0xd8,0x00,0xff},{0xde,0x00,0xff},
  {0xe4,0x00,0xff},{0xea,0x00,0xff},{0xf0,0x00,0xff},{0xf6,0x00,0xff},{0xfc,0x00,0xff},{0xff,0x00,0xfc},{0xff,0x00,0xf6},{0xff,0x00,0xf0},
  {0xff,0x00,0xea},{0xff,0x00,0xe4},{0xff,0x00,0xde},{0xff,0x00,0xd8},{0xff,0x00,0xd1},{0xff,0x00,0xcb},{0xff,0x00,0xc5},{0xff,0x00,0xc0},
  {0xff,0x00,0xba},{0xff,0x00,0xb4},{0xff,0x00,0xae},{0xff,0x00,0xa8},{0xff,0x00,0xa1},{0xff,0x00,0x9b},{0xff,0x00,0x95},{0xff,0x00,0x8f},
  {0xff,0x00,0x89},{0xff,0x00,0x83},{0xff,0x00,0x7e},{0xff,0x00,0x78},{0xff,0x00,0x72},{0xff,0x00,0x6c},{0xff,0x00,0x66},{0xff,0x00,0x60},
  {0xff,0x00,0x5a},{0xff,0x00,0x54},{0xff,0x00,0x4e},{0xff,0x00,0x48},{0xff,0x00,0x41},{0xff,0x00,0x3c},{0xff,0x00,0x36},{0xff,0x00,0x30},
  {0xff,0x00,0x2a},{0xff,0x00,0x24},{0xff,0x00,0x1e},{0xff,0x00,0x18},{0xff,0x00,0x11},{0xff,0x00,0x0b},{0xff,0x00,0x05},{0xff,0x00,0x00}
};
  
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

unsigned char * tripleize(unsigned char * buffer, unsigned int length)
{
  unsigned char * output = NULL;
  unsigned int i = 0;
  unsigned char tmp = 0;
  unsigned int i3 = 0;
  output = malloc(3*length*sizeof(unsigned char));
  for (i=0;i<length;i++)
  {
    tmp = buffer[i];
    i3 = 3*i;
    output[i3  ] = tmp;
    output[i3+1] = tmp;
    output[i3+2] = tmp;
  }
  return output;
}

unsigned char * colorize(unsigned char * buffer, unsigned int length)
{
  unsigned char * output = NULL;
  unsigned int i = 0;
  output = malloc(3*length*sizeof(unsigned char));
  for (i=0;i<length;i++){memcpy(&output[3*i],color[buffer[i]],3);}
  return output;
}
void write_ppm(unsigned char ** data, unsigned char * filename)
{
  FILE * file;
  unsigned int i = 0;
  file = fopen((const) filename,"w");
  fwrite("P6 256 256 255 ",15,1,file);
  for (i=0;i<256;i++) {fwrite(colorize(data[i],256),256*3,1,file);}
  fclose(file);
}
unsigned char * random_buffer(void)
{
  unsigned char * output = NULL;
  unsigned int i = 0;
  output = malloc(256*sizeof(unsigned char));
  for (i=0;i<256;i++) {output[i] = (unsigned char)random();}
  return output;
}
int main (int argc, char * argv[])
{
  srandom(time(NULL));
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int counter = 0;
  unsigned char ** data = NULL;
  unsigned int ** storage = NULL;

  data = malloc(256*sizeof(unsigned char *));
  for (i=0;i<256;i++) {data[i] = malloc(256*sizeof(unsigned char));}
  storage = malloc(256*sizeof(unsigned int *));
  for (i=0;i<256;i++) {storage[i] = malloc(256*sizeof(unsigned int));}

  puts("calculation..");
  for (counter=0;counter<MAX_ITERATIONS;counter++)
  {
    /* fill data with 256 rc4 initialized buffers */
    for (i=0;i<256;i++){memcpy(data[i],init_buffer(random_buffer(),256),256);}
    /* store results in storage */
    for (i=0;i<256;i++){for (j=0;j<256;j++){storage[data[i][j]][j]++;}}
  }

  puts("maximum detection..");
  /* find storage maximum */
  counter = storage[0][0];
  for (i=0;i<256;i++){for (j=0;j<256;j++){if( storage[i][j] > counter ){ counter = storage[i][j] ;}}}

  puts("rendering..");
  /* make image */
  for (i=0;i<256;i++){for (j=0;j<256;j++){data[i][j] = (unsigned char)(0xff*(storage[i][j]/(float)counter));}}

  
  write_ppm(data,(unsigned char *)"output.ppm");
  return EXIT_SUCCESS;
}
