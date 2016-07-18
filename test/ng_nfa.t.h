#ifndef NG_NFA_T___H
#define NG_NFA_T___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  // forward declarations
  typedef struct ng_nfa ng_nfa_t;

  // debugging
  void ng_nfa_dump(const ng_nfa_t* self);

#ifdef __cplusplus
};
#endif

#endif  // end of include guard


