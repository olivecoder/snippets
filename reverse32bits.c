/* 
   Reverse bit pattern (32 bits)
   By Robert Oliveira
*/

#include <stdio.h>
#include <assert.h> 

int reverse(int i) {
    int output;	
    assert sizeof(i)*8 == 32;
    __asm__(
     "nextbit:"
        "rcll $1, %%eax;"
        "rcrl $1, %%ebx;"
        "loop nextbit;"
	 : "=b" (output)
	 : "a" (i), "c" 32 );
	return output;
}

