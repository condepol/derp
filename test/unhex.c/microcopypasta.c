# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
unsigned char v(unsigned char x){if(x<58){return x%48;}else{return(x%32)+9;}}int main(int a,char*V[]){unsigned char b[1024];ssize_t l=0;unsigned int i=0;int f=0;if(a>1){f=open(V[1],114);}while((l=read((int)f,b,1024))>0){for(i=0;i<l;i+=2){putchar((v(b[i])<<4)+v(b[i+1]));}}return EXIT_SUCCESS;}
