#ifndef NG_UTIL_IO__H
#define NG_UTIL_IO__H

#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  // returns NULL on error.  Otherwise
  // return a pointer to the buffer.
  // user takes ownership of the memory
  // allocated for the buffer.
  char* loadFileIntoBuffer(const char* filename,
			   char** buffer);
  
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
