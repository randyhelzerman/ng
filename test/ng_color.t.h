#ifndef NG_COLOR_T__H
#define NG_COLOR_T__H

#include <stdbool.h>

// forward declaratios

typedef struct ng_color ng_color_t;

#ifdef __cplusplus
extern "C" {
#endif
  
  // debugging
  void ng_color_dump(const ng_color_t* self);
  
#ifdef __cplusplus
};
#endif

#endif
