typedef struct {
  unsigned char iv [3];
  unsigned char key_index;
  unsigned char * data;
  unsigned int data_length;
  unsigned char * crc;
} wep_packet;

wep_packet read_packet (const unsigned char * buffer, unsigned int length)
{
  wep_packet output;
  memcpy(output.iv,&buffer[24],3);
  output.key_index = buffer[27]>>6;/* throw the 6 padding bits */
  output.data_length = length-28;
  output.data = malloc(output.data_length);/* include crc in data */
  memcpy(output.data,&buffer[28],output.data_length);
  output.crc = &output.data[output.data_length-4];/* crc = 4 last data bytes*/
  return output;
}

wep_packet copy_packet(wep_packet * source)
{
  wep_packet output;
  output.key_index = source->key_index;
  output.data_length = source->data_length;
  output.data = malloc(output.data_length);
  memcpy(output.data,source->data,output.data_length); 
  memcpy(output.iv,source->iv,3); /* IV is 24 bits */
  output.crc = &output.data[output.data_length-4];/* crc = 4 last data bytes*/
  return output;
}


void recopy_packet(wep_packet * source,wep_packet * destination)
{
  //output.key_index = source->key_index;
  //output.data_length = source->data_length;
  //output.data = malloc(output.data_length);
  /* rewrite data */
  memcpy(destination->data,source->data,destination->data_length); 
  //memcpy(output.iv,source->iv,3); /* IV is 24 bits */
  //output.crc = &output.data[output.data_length-4];/* crc = 4 last data bytes*/
}

void free_wep_packet(wep_packet * pkt)
{
  free(pkt->data);
}
