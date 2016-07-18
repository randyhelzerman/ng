#include <ng_nfa.h>

#include<stdio.h>
#include<stdlib.h>

#include<ng_vector.h>
#include<ng_nfa_state.h>


// constructors
ng_nfa_t*
ng_nfa_new()
{
  ng_nfa_t* self = (ng_nfa_t*)malloc(sizeof(ng_nfa_t));
  return ng_nfa_init(self);
}
 

ng_nfa_t*
ng_nfa_init(ng_nfa_t* self)
{
  self->states_ = ng_vector_new(sizeof(ng_nfa_state_t*), 10);
  return self;
}


// destructors
void
ng_nfa_delete(ng_nfa_t** selfp)
{
  ng_nfa_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void
ng_nfa_uninit(ng_nfa_t* self)
{
  for(int i=0;i<self->states_->numb_;i++){
    ng_nfa_state_delete((ng_nfa_state_t**)
			ng_vector_at(self->states_,
				     i,
				     sizeof(ng_nfa_state_t*)));
  }
  
  ng_vector_delete(&(self->states_),
		   sizeof(ng_nfa_state_t*),0x0);
}


// access

// adds a new state.  Takes ownership of the memory of the state.
// decallocated when the nfa is deallocated.
void
ng_nfa_batch_add_state(ng_nfa_t* self, ng_nfa_state_t* state)
{
  ng_vector_push_back(&self->states_,
		      sizeof(ng_nfa_state_t*),
		      (void*)(&state), 0x0, 0x0);
}


// sort states by their names.
void
ng_nfa_end_batch_add_state(ng_nfa_t* self)
{
  qsort(self->states_,
	self->states_->numb_,
	sizeof(ng_interval_t*),
	(int(*)(const void*,
		const void*))ng_nfa_state_p_compare_);
}


// debugging
void
ng_nfa_dump(const ng_nfa_t* self)
{
  for(int i=0;i<self->states_->numb_;i++){
    printf("%3d: ", i);
    ng_nfa_state_dump(*(ng_nfa_state_t**)ng_vector_at((void*)self->states_,
						      i,
						      sizeof(ng_nfa_state_t*)),
		      // indent the arcs by 3 spaces
		      3);
  }
}


// private functions


// for sorting the states according to their names
int
ng_nfa_state_p_compare_(ng_nfa_state_t** state1,
			ng_nfa_state_t** state2)
{
  return ng_nfa_state_compare(*state1, *state2);
}					     
