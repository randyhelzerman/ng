#include <ng_interval.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// create a new interval
ng_interval_t* ng_interval_eq_new(const char* word, const int max_next_states)
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


// create a new interval-- word is 1 greater than word
ng_interval_t* ng_interval_gt_new(const char* word, 
				  const int max_next_state)
{
  // create it the normal way
  ng_interval_t* self = ng_interval_gt_new(word, max_next_state);
  if(0x0==self) return 0x0;
  
  // then increment the last byte. Works for UTF-8
  const size_t len = strlen(ng_interval_word(self));
  if(0x0 != self->long_word_){
    self->long_word_[len]++;
  } else {
    self->short_word_[len]++;
  }
  
  return self;
}
  

// free it up again
void ng_interval_delete(ng_interval_t** selfp)
{
  free(*selfp);
  *selfp = 0x0;
}


// get the word of this interval
const char* ng_interval_word(const ng_interval_t* self)
{
  if(self->long_word_) return self->long_word_;
  return self->short_word_;
}


// compare -- suitable for sorting
int compare(const ng_interval_t* int1,
	    const ng_interval_t* int2)
{
  // sort on the lexicographic ordering of the word
  return strcmp(ng_interval_word(int1),
		ng_interval_word(int2));
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
						
