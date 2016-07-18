#ifndef NG_VECTOR_T___H
#define NG_VECTOR_T___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_vector ng_vector_t;
  
  // debugging
  void ng_vector_dump(const ng_vector_t* self, const int fruit_size,
		      void(*fruit_dump)(const void*));
  
#ifdef __cplusplus
};
#endif

#endif

