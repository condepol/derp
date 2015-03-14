# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pcap/pcap.h>

void error (const char * msg) {fprintf(stderr,"\x1b[31m[ ! ] %s\n\x1b[0m",msg);}
void info  (const char * msg) {fprintf(stdout,"\x1b[34m[ + ] %s\n\x1b[0m",msg);}

int main(int argc, char * argv []) {
  char * error_buffer [PCAP_ERRBUF_SIZE];
  pcap_t * file_handle;
  const char * filter_string = "llc";
  struct bpf_program filter_struct;

  /* 1. read input .cap */
  if (argc != 2) {
    info("Usage : ./pixie <capture.cap>");
    return 1;
  } else {
    if (strncmp((const char *)(((unsigned long int)argv[1]) + (strlen(argv[1]) - 4)), (const char *) ".cap", 4) == 0) {
      file_handle = pcap_open_offline(argv[1],(char *)error_buffer);
      if (file_handle == NULL) {
        error("pcap_open_offline failed !");
        return 1;
      }
    } else {
      error("Extension should be .cap");
      info("Usage : ./pixie <capture.cap>");
      return 1;
    }
  }
  
  /* 2. filter LLC/EAP/WPS packets */
  pcap_compile(file_handle, &filter_struct, filter_string, 0, 0);

  /* 3. free memory, close file*/
  pcap_freecode(&filter_struct);
  pcap_close(file_handle);
  return 0;
}
