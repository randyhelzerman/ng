#ifndef NG_NFA_STATE___H
#define NG_NFA_STATE___H

#include<stdlib.h>
#include<stdbool.h>

// forward declarations
typedef struct ng_vector ng_vector_t;
typedef struct ng_interval ng_interval_t;

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_nfa_state {
    void* action_;  // whatever action we should taek in this state
    ng_vector_t* arcs_;
  } ng_nfa_state_t;
  
  // constructors
  ng_nfa_state_t* ng_nfa_state_new();
  ng_nfa_state_t* ng_nfa_state_init(ng_nfa_state_t* self);
  
  // destructors
  void ng_nfa_state_delete(ng_nfa_state_t** selfp);
  void ng_nfa_state_uninit(ng_nfa_state_t* self);
  
  // access
  
  // adds an interval
  void ng_nfa_state_add_interval(ng_nfa_state_t* self,
				 const ng_interval_t* interval);
  
  // debugging
  void ng_nfa_state_dump(const ng_nfa_state_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
