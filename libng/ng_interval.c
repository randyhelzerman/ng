#include <ng_interval.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


const size_t NG_INTERVAL_MAX_SHORT_WORD_SIZE  = 10;
const size_t NG_INTERVAL_MAX_NEXT_STATES_SIZE = 10;


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
  ng_interval_t* self = ng_interval_eq_new(word, max_next_state);
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


// copy and init interval into blank memory space.  tgt must be pre-allocated
// to be large enough.
ng_interval_t* ng_interval_cp_init(const ng_interval_t* self, ng_interval_t* tgt)
{
  // copy over the word
  if(0x0 != self->long_word_) strcpy(tgt->long_word_, self->long_word_);
  else {
    tgt->long_word_ = 0x0;
    strncpy(tgt->short_word_, self->short_word_, 10);
  }
  
  // copy over color info
  tgt->max_next_states_ = self->max_next_states_;
  tgt->numb_next_states_ = self->numb_next_states_;
  ng_color_t* self_colors = (ng_color_t*)self->next_states_;
  ng_color_t* tgt_colors  = (ng_color_t*)tgt->next_states_;
  for(int i=0;i<self->numb_next_states_;i++){
    tgt_colors[i] = self_colors[i];
  }
  
  return tgt;
}


// free it up again
void ng_interval_delete(ng_interval_t** selfp)
{
  // clean up the memory used by this
  ng_interval_deinit(*selfp);

  // free it
  free(*selfp);

  // set pointer equal to NULL
  *selfp = 0x0;
}


// de-initialzie memory region; no dealllocion.
void ng_interval_deinit(ng_interval_t* self)
{
  if(0x0 != self->long_word_){
    free(self->long_word_);
  }
}


//-----------------
// access functions
//-----------------

// get the size of this interval.  Because its expandable,
// its not just sizeof(rg_interval_t).
size_t ng_interval_sizeof(const ng_interval_t* self)
{
  return (sizeof(ng_interval_t) +
	  self->max_next_states_ * sizeof(ng_color_t));
}


// get the word of this interval
const char* ng_interval_word(const ng_interval_t* self)
{
  if(self->long_word_) return self->long_word_;
  return self->short_word_;
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
  printf("ng_interval [%s...) next_states[", ng_interval_word(self));
  
  // print out the next states
  int first=1;
  for(int i=0;i<self->numb_next_states_;i++){
    // dork with commas
    if(!first) { printf(","); }
    first=0;
    
    // print the next state
    ng_color_dump(&self->next_states_[i]);
  }
  printf("]\n");
}
						
