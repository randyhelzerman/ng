#ifndef NG_INTERVAL_T__H
#define NG_INTERVAL_T__H

#include <stdbool.h>
#include <stdlib.h>
#include <ng_color.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_interval ng_interval_t;

  // debugging
  void ng_interval_dump(const ng_interval_t* self);
  
  
#ifdef __cplusplus
};
#endif

#endif // incude guard
