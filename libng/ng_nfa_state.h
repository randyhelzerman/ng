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
    char*    name_;       // name of this stae
    void*    action_;     // whatever action we should taek in this state
    ng_vector_t* arcs_;
  } ng_nfa_state_t;
  
  // constructors
  ng_nfa_state_t* ng_nfa_state_new(const char* name);
  ng_nfa_state_t* ng_nfa_state_init(ng_nfa_state_t* self,
				    const char* name);
  
  // destructors
  void ng_nfa_state_delete(ng_nfa_state_t** selfp);
  void ng_nfa_state_uninit(ng_nfa_state_t*  self);
  
  // access
  
  // adds an interval
  void ng_nfa_state_add_interval(ng_nfa_state_t* self,
				 const ng_interval_t* interval);
  
  int ng_nfa_state_compare(const ng_nfa_state_t* state1,
			   const ng_nfa_state_t* state2);
  
#ifdef __cplusplus
};
#endif

#endif  // end of include guard
