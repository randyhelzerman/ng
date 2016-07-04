#ifndef NG_INTERVAL__H
#define NG_INTERVAL__H

#include <ng_color.h>

#ifdef __cplusplus
extern "C" {
#endif


  typedef struct {
    char    short_word_[10];     // most words fit here
    char*   long_word_;          // if its too long, this is allocaated/populated/non-null
  
    // set of next states
    int     max_next_states_;     // how much space is allocated for the next states
    int     numb_next_states_;    // how much space is actually used for next states
    int    next_states_[];        // ugly as sin, I know, but fast as hell
  } ng_interval_t;


  // create a new interval-- word is equal to word
  ng_interval_t* ng_interval_eq_new(const char* word, const int max_next_state);
  
  // create a new interval-- word is 1 greater than word
  ng_interval_t* ng_interval_gt_new(const char* word, const int max_next_state);
  
  // free it up again
  void ng_interval_delete(ng_interval_t** selfp);
  
  // access functions
  
  // get the word of this interval.
  const char* ng_interval_word(const ng_interval_t* self);
  
  // compare -- suitable for sorting
  int compare(const ng_interval_t* int1,
	      const ng_interval_t* int2);
  
  // debugging
  void ng_interval_dump(const ng_interval_t* self);
  
  
#ifdef __cplusplus
};
#endif

#endif

