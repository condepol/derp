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


