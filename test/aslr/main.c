# include <stdio.h>
# include <stdlib.h>

void nopnop(void) {
  asm("nop");
}
unsigned long getEBP(void){
  asm("movl %ebp, %eax") ;
}
unsigned long getESP(void){
  asm("movl %esp, %eax") ;
}

int main(void){
  printf("ESP:%x\n",getESP());
  printf("EBP:%x\n",getEBP());
}
