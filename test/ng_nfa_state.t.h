#ifndef NG_NFA_STATE_T___H
#define NG_NFA_STATE_T___H

#include<stdlib.h>
#include<stdbool.h>

// forward declarations
typedef struct ng_vector ng_vector_t;
typedef struct ng_interval ng_interval_t;

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_nfa_state ng_nfa_state_t;
  
  // debugging
  void ng_nfa_state_dump(const ng_nfa_state_t* self, const int indent);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard

