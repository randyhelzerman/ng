#include <ng_nfa_state.h>


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

