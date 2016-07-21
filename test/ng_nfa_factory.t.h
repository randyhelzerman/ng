#ifndef NG_NFA_FACTORY_T__H
#define NG_NFA_FACTORY_T__H

#include<stdlib.h>
#include<stdbool.h>

// forward declarations
typedef struct ng_nfa_factory nf_nfa_factory_t;

#ifdef __cplusplus
extern "C" {
#endif
  
  void ng_nfa_factory_dump(ng_nfa_factory_t *self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard

