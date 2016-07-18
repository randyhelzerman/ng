#include <ng_nfa_state.h>
#include <ng_nfa_state.t.h>


// debuggingb
void ng_nfa_state_dump(const ng_nfa_state_t* self, const int indent)
{
  // first, print out a graphical representation of the intervals
  for(int i=0;i<self->arcs_->numb_;i++){
    // grab the arc at the position
    const ng_interval_t* interval
      = (ng_interval_t* )ng_vector_at(self->arcs_,sizeof(ng_interval_t),i);
    
    printf("[%s------------)", interval->word_);
  }
  printf("\n");

  // now print out the associated next states
  bool moreToPrint=true;
  int nextStateIndex = 0;
  while(moreToPrint){
    bool foundMoreToPrint = false;
    
    // indent for arc
    for(int i=0;i<indent;i++){
      printf(" ");
    }
    
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
	printf("     ");
      } else {
	// no more states to print on this one, so just space over
	printf("           ");
      }
    }
    printf("\n");
    
    nextStateIndex++;
    
    // see if there's anything else to do
    if(!foundMoreToPrint) moreToPrint = false;
  }
}

