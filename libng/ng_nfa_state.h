#ifndef NG_NFA_STATE___H
#define NG_NFA_STATE___H

#include<stdlib.h>
#include<stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct ng_nfa_state {
    void* action_;  // whatever action we should taek in this state
    ng_vector_t* arcs_;
  } ng_nfa_state_tt;
  
  // constructors
  ng_nfa_t* ng_nfa_state_new();
  ng_nfa_t* ng_nfa_state_init(ng_nfa_t* self);
  
  // destructors
  void ng_nfa_state_delete(ng_nfa_t** selfp);
  void ng_fa_state_deinit(ng_nfa_t* self);
  
  // access
  
  // adds a a transition to a state.  This is a very
  // low-level function, probably not the one you want.
  void ng_nfa_state_add_transition(const char*);
  
  // debugging
  void ng_nfa_state_dump(const ng_nfa_t* self);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
