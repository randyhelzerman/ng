#include<ng_interval.h>
#include<ng_interval.t.h>

#include<ng_color.t.h>

#include<stdio.h>

// debugging
void ng_interval_dump(const ng_interval_t* self)
{
  // print out the word
  printf("ng_interval [\"%s\"...) next_states[",
	 ng_interval_word(self));
  
  // print out the next states
  int first=1;
  for(int i=0;i<self->numb_next_states_;i++){
    // dork with commas
    if(!first) { printf(","); }
    first=0;
    
    // print the next state
    ng_color_dump(&self->next_states_[i]);
  }
  printf("] ");
}

