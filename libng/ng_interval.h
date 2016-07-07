#ifndef NG_INTERVAL__H
#define NG_INTERVAL__H

#include <stdbool.h>
#include <stdlib.h>
#include <ng_color.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct {
    // fits most words.
    union {
      char word_prefix_[NG_INTERVAL_MAX_WORD_PREFIX_SIZE];
      
      struct {
	// if this is 0x0, then the long word is in use.  
	char sentinal;
	char* letters_
      } long_word_;
    };
    
    // set of next states
    union {
      ng_color_t next_states_prefix_[NG_INTERVAL_MAX_NEXT_STATES_PREFIX_SIZE];
      
      struct {
	ng_color_t sentinal_;
	ng_color_t* next_states_;
      } long_next_states_;
    }; 
  } ng_interval_t;
  
  
  // create a new interval-- word is equal to word
  ng_interval_t* ng_interval_eq_new(const char* word,
				    const int max_next_state);
  
  ng_interval_t* ng_interval_eq_init(ng_interval_t* self,
				     const char* word,
				     const int max_next_state);
  
  // create a new interval-- word is 1 greater than word
  ng_interval_t* ng_interval_gt_new(const char* word,
				    const int max_next_state);
  
  // copy and init interval into blank memory space.  tgt must be pre-allocated
  // to be large enough.
  ng_interval_t* ng_interval_cp_init(const ng_interval_t* self,
				     ng_interval_t* tgt);
  
  // free it up again
  void ng_interval_delete(ng_interval_t** selfp);

  // de-initialzie memory region; no dealllocion.
  void ng_interval_deinit(ng_interval_t* self);
  
  // access functions

  // get the size of this interval.  Because its expandable,
  // its not just sizeof(rg_interval_t).
  size_t ng_interval_sizeof(const ng_interval_t* self);
  
  // get the word of this interval.
  const char* ng_interval_word(const ng_interval_t* self);
  
  // compare -- suitable for sorting
  int ng_interval_compare(const ng_interval_t* int1,
			  const ng_interval_t* int2);
  
  bool ng_interval_equal(const ng_interval_t* int1,
			 const ng_interval_t* int2);
  
  // debugging
  void ng_interval_dump(const ng_interval_t* self);
  
  
#ifdef __cplusplus
};
#endif


#endif // ifndef NG_INTERVAL__H
