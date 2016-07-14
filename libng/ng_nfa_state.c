#include <ng_nfa_state.h>

#include<stdio.h>
#include<string.h>

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
  ng_vector_delete(&(self->arcs_),
		   sizeof(ng_interval_t),
		   (void(*)(void*))ng_interval_uninit);
}


// access

// adds an interval
void ng_nfa_state_add_interval(ng_nfa_state_t* self,
			       const ng_interval_t* interval)
{
  ng_vector_push_back(&self->arcs_,
		      sizeof(ng_interval_t), (const void*)interval,
		      (void *(*)(const void *, void *))ng_interval_cp_init,
		      (void (*)(void *))ng_interval_uninit);
}		      


// debuggingb
void ng_nfa_state_dump(const ng_nfa_state_t* self)
{
  // first, print out a graphical representation of the intervals
  for(int i=0;i<self->arcs_->numb_;i++){
    // grab the arc at the position
    const ng_interval_t* interval
      = (ng_interval_t* )ng_vector_at(self->arcs_,sizeof(ng_interval_t),i);
    
    printf("[%s--------)", interval->word_);
  }
  printf("\n");

  // now print out the associated next states
  bool moreToPrint=true;
  int nextStateIndex = 0;
  while(moreToPrint){
    bool foundMoreToPrint = false;
    
    for(int i=0;i<self->arcs_->numb_;i++){
      // grab the arc at the position
      const ng_interval_t* interval
	= (ng_interval_t* )ng_vector_at(self->arcs_, sizeof(ng_interval_t),i);
      
      // space over an apropos amount
      const int numbSpaces = 3 + strlen(interval->word_);
      for(int j=0;j<numbSpaces;j++){
	printf(" ");
      }
      
      // see if there are any more states to print out
      if(nextStateIndex < interval->numb_next_states_){
	foundMoreToPrint = true;
	
	// print the next state
	printf("%3d-%2d",
	       interval->next_states_[nextStateIndex].state_,
	       interval->next_states_[nextStateIndex].delta_);

	// space over the rest of the way
	printf("    ");
      } else {
	// no more states to print on this one, so just space over
	printf("            ");
      }
    }
    printf("\n");
    
    nextStateIndex++;
    
    // see if there's anything else to do
    if(!foundMoreToPrint) moreToPrint = false;
  }
}

