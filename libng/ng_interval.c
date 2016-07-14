#include <ng_interval.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


const size_t NG_INTERVAL_MAX_SHORT_WORD_SIZE  = 10;
const size_t NG_INTERVAL_MAX_NEXT_STATES_SIZE = 10;


// create a new interval
ng_interval_t* ng_interval_eq_new(const char* word)
{
  // allocate it
  ng_interval_t* self = (ng_interval_t*)malloc(sizeof(ng_interval_t));
  if(0x0==self) return 0x0;
  
  return ng_interval_eq_init(self,word);
}


ng_interval_t* ng_interval_eq_init(ng_interval_t* self, const char* word)
{
  // initialize it
  strncpy(self->word_, word, 15);
  self->numb_next_states_ = 0;
  
  return self;
}


// create a new interval-- word is 1 greater than word
ng_interval_t* ng_interval_gt_new(const char* word)
{
  // allocate it
  ng_interval_t* self = (ng_interval_t*)malloc(sizeof(ng_interval_t));
  if(0x0==self) return 0x0;
  
  return ng_interval_gt_init(self,word);
}

ng_interval_t* ng_interval_gt_init(ng_interval_t* self, const char* word)
{
  // initialize it
  strncpy(self->word_, word, 15);
  self->numb_next_states_ = 0;
  
  // then increment the last byte. Works for UTF-8
  const size_t len = strlen(ng_interval_word(self));
  self->word_[len-1]++;
  
  return self;
}


// copy and init interval into blank memory space.  tgt must be pre-allocated
// to be large enough.
ng_interval_t* ng_interval_cp_init(const ng_interval_t* self, ng_interval_t* tgt)
{
  strncpy(tgt->word_, self->word_, 15);
  
  // copy over color info
  tgt->numb_next_states_ = self->numb_next_states_;
  for(int i=0;i<self->numb_next_states_;i++){
    ng_color_cp(&self->next_states_[i], &tgt->next_states_[i]);
  }
  
  return tgt;
}


// copy interval into already init-ed memory space
ng_interval_t* ng_interval_cp(const ng_interval_t* self,
			      ng_interval_t* tgt)
{
  return ng_interval_cp_init(self,tgt);
}



// free it up again
void ng_interval_delete(ng_interval_t** selfp)
{
  // clean up the memory used by this
  ng_interval_uninit(*selfp);
  
  // free it
  free(*selfp);

  // set pointer equal to NULL
  *selfp = 0x0;
}


// de-initialzie memory region; no dealllocion.
void ng_interval_uninit(ng_interval_t* self)
{
  // nothing yet to do.
  self->word_[0] = 0x0;
}


//-----------------
// access functions
//-----------------


// get the word of this interval
const char* ng_interval_word(const ng_interval_t* self)
{
  return self->word_;
}


// push a color
bool ng_interval_push_color(ng_interval_t* self,
			    const int state,
			    const int delta)
{
  // see if we have enough room
  if(self->numb_next_states_ >=16) return false;
  
  // copy it onto the apropos place
  ng_color_init(&self->next_states_[self->numb_next_states_],
		state,
		delta);
  
  // increment the stack pointer
  self->numb_next_states_++;
  
  // return success
  return true;
}


// compare -- suitable for sorting
int ng_interval_compare(const ng_interval_t* int1,
			const ng_interval_t* int2)
{
  // sort on the lexicographic ordering of the word
  return strcmp(ng_interval_word(int1),
		ng_interval_word(int2));
}


// test for semantic equality of the intervals
bool ng_interval_equal(const ng_interval_t* int1,
		       const ng_interval_t* int2)
{
  // compare words for equality
  if(0 != strcmp(ng_interval_word(int1),
		 ng_interval_word(int2))){
    return false;  // strings are not equal 
  }
  
  // must have same number of next states
  if(int1->numb_next_states_ != int2->numb_next_states_){
    return false;
  }
  
  // since we maintain them as being sorted,
  // we can just compare
  for(int i=0;i<int1->numb_next_states_;i++){
    if(!ng_color_equal(&int1->next_states_[i],
		       &int2->next_states_[i])){
      return false;
    }
  }

  return true;
}


// debugging
void ng_interval_dump(const ng_interval_t* self)
{
  // print out the word
  printf("ng_interval [\"%s\"...) next_states[", ng_interval_word(self));
  
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
						
