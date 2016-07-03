#ifndef NG_INTERVAL__H
#define NG_INTERVAL__H


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


// create a new interval
ng_interval_t* ng_interval_new(const char* word, const int max_next_state);

// access functions

// get the word of this interval.
const char* ng_interval_word(const ng_interval_t* self);

// debugging
void ng_interval_dump(const ng_interval_t* self);

#ifdef __cplusplus
};
#endif

#endif

