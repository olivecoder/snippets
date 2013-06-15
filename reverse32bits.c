/* 
   Reverse bit pattern (32 bits)
   By Robert Oliveira
*/

#include <stdio.h>

int reverse(int i) {
	int output;
	__asm__(
     "nextbit:"
        "rcll $1, %%eax;"
        "rcrl $1, %%ebx;"
        "loop nextbit;"
	 : "=b" (output)
	 : "a" (i), "c" (sizeof(i)*8) );
	return output;
}

