#ifndef NG_NFA___H
#define NG_NFA___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  // forward declarations
  typedef struct ng_vector ng_vector_t;
  typedef struct ng_nfa_state ng_nfa_state_t;
  
  typedef struct ng_nfa {
    ng_vector_t* states_;
  } ng_nfa_t;
  
  // constructors
  ng_nfa_t* ng_nfa_new();
  ng_nfa_t* ng_nfa_init(ng_nfa_t* self);
  
  // destructors
  void ng_nfa_delete(ng_nfa_t** selfp);
  void ng_nfa_uninit(ng_nfa_t* self);
  
  // access
  
  // adds a new state. 
  void
  ng_nfa_batch_add_state(ng_nfa_t* self,
			 ng_nfa_state_t* state);
  
  // sort states by their names. Call after
  // adding all the states
  void
  ng_nfa_end_batch_add_state(ng_nfa_t* self);
  
  // private functions
  
  // for sorting the states according to their names
  int ng_nfa_state_p_compare_(ng_nfa_state_t** state1,
			      ng_nfa_state_t** state2);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard

