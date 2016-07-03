#include <ng_interval.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// create a new interval
ng_interval_t* ng_interval_new(const char* word, const int max_next_states)
{
  // calcualte size
  const size_t size = sizeof(ng_interval_t) + max_next_states*sizeof(int);
  
  // allocate it
  ng_interval_t* self = (ng_interval_t*)malloc(size);
  if(0x0==self) return 0x0;
  
  // initialize it
  const size_t word_length = strlen(word);
  if(word_length > 9) {
    // we have to allocated the long word
    self->long_word_ = strdup(word);
  } else {
    // just copy to short word
    strcpy(self->short_word_, word);
    self->long_word_ = 0x0;
  }
  
  self->max_next_states_  = max_next_states;
  self->numb_next_states_ = 0;

  return self;
}

// get the word of this interval
const char* ng_interval_word(const ng_interval_t* self)
{
  if(self->long_word_) return self->long_word_;
  return self->short_word_;
}


// debugging
void ng_interval_dump(const ng_interval_t* self)
{
  // print out the word
  printf("ng_interval [%s...) next_states[", ng_interval_word(self));
  
  // print out the next states
  int first=1;
  for(int i=0;i<self->numb_next_states_;i++){
    // dork with commas
    if(!first) { printf(","); }
    first=0;
    
    // print the next state
    printf("%d", self->next_states_[i]);
  }
  printf("]\n");
}
						
