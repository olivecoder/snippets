/*
  implements go language defer in C language
  by Robert Oliveira
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef void (*deferred)(void *);
inline void *get_retp(void) __attribute__((always_inline));
inline void *set_ret(void *) __attribute__((always_inline));
inline void defer(deferred func, void *arg) __attribute__((always_inline));

void *original_ret;
deferred deferred_func;
void * deferred_arg;

void *get_retp(void)   {
  // returns a pointer to the return address in stack
  void *retp = __builtin_frame_address(0);  
  void *(*bp) = (void **) retp;
  return &(bp[1]);
}

inline void * set_ret(void *new_ret) {
  // set new function return address
  void *(*bp) = (void **) __builtin_frame_address(0);
  void *old_ret = bp[1];
  bp[1] = new_ret;
  return old_ret;
}

int test_frame_format(void) {
  void *caller_retp = __builtin_frame_address(1);  
  void *caller_ret = __builtin_return_address(1);
  void *(*bp) = (void **) caller_retp;
  return caller_ret == bp[1];
}

int test_get_retp(void) { 
  void *caller_ret = __builtin_return_address(0);
  void **retp = get_retp();
  return caller_ret == *retp;
}

void run_deferred(void) {
  printf("Checkpoint: running deferred functions\n");
  set_ret(original_ret);
  printf("Checkpoint: levaing run_deferred\n");
  fflush(stdout);
} 

void defer(deferred func, void *arg) {
  deferred_func = func;
  deferred_arg = arg;
  original_ret = set_ret(run_deferred);
}

int temp(deferred func, void *arg) {
  /*
  __asm__(
	  ""
	  // "movl $32, %%ecx;"
     "reverse:"
	"rcll $1, %%eax;"
        "rcrl $1, %%ebx;"
        "loop reverse;"
	: "=b" (output)
	: "a" (i), "c" (sizeof(i)*8) );
  return output;
  */
}


int zeroint(int *i) {
  *i = 0;
  printf("deferred: i = %i", *i);
  return *i;
}


int test_defer(int i) {
  printf("checkpoint 1: i = %i\n", i++);
  defer((deferred)zeroint, (void *)&i);
  printf("checkpoint 2: i = %i\n", i++);
  return i;
}


int main() {
  assert(test_frame_format());
  assert(test_get_retp());
  printf("test: %i\n", test_frame_format());
  test_defer(1);
  return 0;
}

