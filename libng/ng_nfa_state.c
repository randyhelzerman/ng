#include <ng_nfa_state.h>

#include <ng_vector.h>
#include <ng_interval.h>

// constructors
ng_nfa_state_t* ng_nfa_state_new()
{
  // allocate the memory
  ng_nfa_state_t* self = (ng_nfa_state_t*)malloc(sizeof(ng_nfa_state_t));

  // initialize it
  return ng_nfa_state_init(self);
}


ng_nfa_state_t* ng_nfa_state_init(ng_nfa_state_t* self)
{
  // initialize the action...nothing for now
  self->action_ = 0x0;
  
  // initialize the arcs.  I don't know what to put for initial max so
  // just pick a number.
  self->arcs_ = ng_vector_new(sizeof(ng_interval_t), 10);

  return self;
}

  
// destructors
void ng_nfa_state_delete(ng_nfa_state_t** selfp)
{
  ng_nfa_state_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_nfa_state_uninit(ng_nfa_state_t* self)
{
  ng_vector_delete(&self->arcs_,
		   sizeof(ng_interval_t),
		   (void(*)(void*))ng_interval_uninit);
}
  

// access

// adds a a transition to a state.  This is a very low-level function,
// probably not the one you want.
void ng_nfa_state_add_transition(const char* token)
{
}


// debuggingb
void ng_nfa_state_dump(const ng_nfa_state_t* self)
{
}

