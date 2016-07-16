#include <ng_nfa.h>

#include<stdlib.h>


// constructors
ng_nfa_t* ng_nfa_new()
{
  ng_nfa_t* self = (ng_nfa_t*)malloc(sizeof(ng_nfa_t));
  return ng_nfa_init(self);
}


ng_nfa_t* ng_nfa_init(ng_nfa_t* self)
{
  return *self;
}


// destructors
void ng_nfa_delete(ng_nfa_t** selfp)
{
  ng_nfa_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_nfa_uninit(ng_nfa_t* self)
{
  for(int i=0;i<self->states_->numb_;i++){
    ng_nfa_state_t* state
      = ng_vector_at(self->states_,sizeof(ng_nfa_state_t*),i);
    ng_dfa_state_uninit(state);
    free(stae);
  }
  
  ng_vector_delete(&(self->states_), sizeof(ng_nfa_state_t*), 0x0);
}


// access

// adds a new state.  Takes ownership of the memory of the state.
// decallocated when the nfa is deallocated.
void
ng_nfa_batch_add_state(ng_nfa_t* self, ng_nfa_state_t* state)
{
  ng_vector_push_back(self->states_,
		      sizeof(ng_nfa_state_t*),
		      (void*)(&state), 0x0, 0x0);
}


// sort states by their names.
void ng_nfa_end_add_batch_state(ng_nfa_t* self)
{
  qsort(self->fruits_,
	self->numb_,
	sizeof(ng_interval_t**),
	(int(*)(void*,void*))ng_nfa_interval_compare_);
}


// debugging
void ng_nfa_dump(const ng_nfa_t* self)
{
  
}


// private functions

// for sorting the states according to their names
int ng_nfa_interval_compare_(ng_interval_t** int1,
			     ng_interval_t** int1)
{
  return ng_interval_compare(*int1, *int2);
}					     
  
