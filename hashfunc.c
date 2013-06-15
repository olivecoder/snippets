/* 
   my hash function
   By Robert Oliveira
*/

#include <stdio.h> 
#include <string.h> 

typedef unsigned int word;
typedef unsigned char byte;

static inline word _hash_word(size_t *left, word w) {
    const static size_t word_bits = sizeof(word) * 8;
    const static word mask = word_bits - 1;  
    *left = (*left + w) & mask;
    return (w >> *left) ^ (w << (word_bits - *left));
}

word hash(const void *data, size_t sz) { 
    word *ptr = (word *) data;
    word result = 100000007;
    size_t left = 17; 
    size_t remaining_words = sz / sizeof(word);
    while (remaining_words--) { 
        result += _hash_word(&left, (word) *ptr++);
    }
    size_t remaining_bytes = sz % sizeof(word);
    if ( remaining_bytes ) {
        // build a padded word for processing 
        word padded = 0; 
        // that will gives a different result depending on endianess
        memcpy(&padded, ptr, remaining_bytes);
        result += _hash_word(&left, padded);
    }    
    return result;
}
