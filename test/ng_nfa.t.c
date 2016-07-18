#include <ng_nfa.h>
#include <ng_nfa.t.h>

#include<stdio.h>

#include <ng_vector.h>
#include <ng_nfa_state.t.h>

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

