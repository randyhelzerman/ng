#ifndef NG_INTERVAL__H
#define NG_INTERVAL__H

#include <stdbool.h>
#include <stdlib.h>
#include <ng_color.h>

#ifdef __cplusplus
extern "C" {
#endif
  
  typedef struct {
    char word_[16];
    ng_color_t next_states_[16];
    int numb_next_states_;
  } ng_interval_t;
  
  
  // create a new interval-- word is equal to word
  ng_interval_t* ng_interval_eq_new(const char* word);
  
  ng_interval_t* ng_interval_eq_init(ng_interval_t* self,
				     const char* word);
  
  // create a new interval-- word is 1 greater than word
  ng_interval_t* ng_interval_gt_new(const char* word);
  
  ng_interval_t* ng_interval_gt_init(ng_interval_t* self,
				     const char* word);
  
  // copy and init interval into blank memory space.  tgt must be pre-allocated
  // to be large enough.
  ng_interval_t* ng_interval_cp_init(const ng_interval_t* self,
				     ng_interval_t* tgt);

  // copy interval into already init-ed memory space
  ng_interval_t* ng_interval_cp_init(const ng_interval_t* self,
				     ng_interval_t* tgt);
  
  // free it up again
  void ng_interval_delete(ng_interval_t** selfp);

  // de-initialzie memory region; no dealllocion.
  void ng_interval_uninit(ng_interval_t* self);
  
  // access functions
  
  // get the word of this interval.
  const char* ng_interval_word(const ng_interval_t* self);

  // push a color
  bool ng_interval_push_color(ng_interval_t* self,
			      const int state,
			      const int delta);
  
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
