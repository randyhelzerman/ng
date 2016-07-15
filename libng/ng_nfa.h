#ifndef NG_NFA___H
#define NG_NFA___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_nfa {
    ng_vector_t* states_;
  } ng_nfa_t;
  
  // constructors
  ng_nfa_t* ng_nfa_new();
  ng_nfa_t* ng_nfa_init(ng_nfa_t* self);
  
  // destructors
  void ng_nfa_delete(ng_nfa_t** selfp);
  void ng_fa_deinit(ng_nfa_t* self);
  
  // access

  // adds a new state. 
  void ng_nfa_batch_add_state(ng_nfa_t* self, ng_nfa_state_t* state);

  // adds a a transition to a state.  This is a very
  // low-level function, probably not the one you want.
  void ng_nfa_add_transition(const char* , const int new_state);

  
  // debugging
  void ng_nfa_dump(const ng_nfa_t* self);
			     
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
