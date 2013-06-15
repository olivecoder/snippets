/*
   Subsequence code golf solution 
   Given strings X and Y, determine whether X is a subsequence of Y. 
   The empty string is regarded as a subsequence of every string. 
   (E.g., '' and 'anna' are subsequences of 'banana'.) 
    
   http://codegolf.stackexchange.com/questions/5529/is-string-x-a-subsequence-of-string-y/8404#8404
   http://ideone.com/BpITZ

   by Robert Oliveira (olivecoder)
*/

int is_subsequence(char *x, char *y) {
	while(*y)*x-*y++?0:x++; // 23 characteres
	return !*x;
}
