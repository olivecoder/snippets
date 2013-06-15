/*
  Write the shortest program in your favourite language to interpret a 
  Brainfuck program. The program is read from a file. Input and output 
  are standard input and standard output.

  Cell size: 8bit unsigned. Overflow is undefined.
  Array size: 30000 bytes (not circled)
  Bad commands are not part of the input
  Comments are everything not in +-.,[]<>
  no EOF symbol
  
  http://codegolf.stackexchange.com/questions/84/interpret-brainfuck/7281#7281
  http://ideone.com/yZHVv

  by Robert Oliveira (olivecoder)
*/

#include<functional>
#include<stdio.h>
main(){
	char b[30000],g[9999],*f=g,*p=b,n[]="+-,.><[]",j;
	std::function<void()>m[]={
		[&p]{(*p)++;},
		[&p]{(*p)--;},
		[&p]{*p=getchar();},
		[&p]{putchar(*p);},
		[&p]{p++;},
		[&p]{p--;},
		[&p,&f]{if(!(*p))while(*f-93)f++;},
		[&f,&m]{while(*f-91)f--;m[6]();}
	};
	fread(g,1,9999,fopen(a[1],0));
	for(;*f;f++)for(j=0;n[j];j++)if(n[j]==*f)m[j]();
}
