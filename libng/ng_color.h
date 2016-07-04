#ifndef NG_COLOR__H
#define NG_COLOR__H


#ifdef __cplusplus
extern "C" {
#endif


  typedef struct {
    int     state_;              // which state to go to next
    int     delta_;              // how many bytes to consume when you go there
  } ng_color_t;
  
  
  // create a new color
  ng_color_t* ng_color_new(const int state, const int delta);
  
  // free it up again
  void ng_color_delete(ng_color_t** selfp);
  
  
  // compare structs -- suitable for use in sorting
  // returns  <0 iff c1 < c2
  //           0 iff c1 ==c2
  //          >0 iff c1 > c2
  int ng_color_compare(const ng_color_t* c1,
		       const ng_color_t* c2);
  
  
  // debugging
  void ng_color_dump(const ng_color_t* self);
  
#ifdef __cplusplus
};
#endif

#endif

