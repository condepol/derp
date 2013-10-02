
unsigned char hexchar(unsigned char x){return ((x+0x30)+((x>9)*0x27));}

unsigned char * hexa (unsigned char * buffer,unsigned int length)
{
  unsigned char * output = NULL;
  output = malloc(1+3*length);
  if (output==NULL) {return (unsigned char *)("unable to allocate string :/");}
  output[3*length] = 0;
  while (length--)
  {
    output[(3*length)+2] = ' ';
    output[(3*length)+1] = hexchar(buffer[length]%16);
    output[(3*length)+0] = hexchar(buffer[length]>>4);
  }
  return output;
}
void print_packet(wep_packet p)
{
  /*
  printf("%20s : %d data bytes\n","Wep packet",p.data_length);
  printf("%20s : %02x%02x%02x\n","IV",p.iv[0],p.iv[1],p.iv[2]);
  printf("%20s : %x\n","Key index",p.key_index);
  printf("%20s : %02x%02x%02x%02x\n","CRC",p.crc[0],p.crc[1],p.crc[2],p.crc[3]);
  */
  printf("Packet \x1b[33mIV:%02x%02x%02x\x1b[36m%2x\x1b[30m %3d \x1b[32mCRC:%02x%02x%02x%02x\x1b[30m\n",p.iv[0],p.iv[1],p.iv[2],p.key_index,p.data_length,p.crc[0],p.crc[1],p.crc[2],p.crc[3]);
}


unsigned char ch1(unsigned char x){if((x>0x1f)&&(x<0x7f)){return 32;}else{return hexchar(x>>4);}}
unsigned char ch2(unsigned char x){if((x>0x1f)&&(x<0x7f)){return x;}else{return hexchar(x%16);}}
unsigned int color(unsigned char x)
{
  switch (x>>5) {
    case 2:
      if (((x-1)%0x20)<0x1b) { return 4+(x>0x60)*2;}
      return 5;
    case 3:
      if (((x-1)%0x20)<0x1b) { return 4+(x>0x60)*2;}
      return 5;
    case 1:
      if (x%0x30<10) {return 1;}
      return 5;
    default:
      return 0;
  }
}


void printbuffer(unsigned char * buffer, unsigned int l)
{
  unsigned int i = 0;
  for (i=0;i<l;i++) {
    printf("\x1b[3%dm%c%c\x1b[0m",color(buffer[i]),ch1(buffer[i]),ch2(buffer[i]));
    if ((i%0x40) == 0x3f) {puts("");};
  }
  puts("");
}
