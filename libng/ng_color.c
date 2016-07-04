#include <ng_color.h>

#include<stdio.h>
#include<stdlib.h>


// create a new color
ng_color_t* ng_color_new(const int state, const int delta)
{
  ng_color_t* self = (ng_color_t*)malloc(sizeof(ng_color_t));
  self->state_ = state;
  self->delta_ = delta;
  return self;
}


void ng_color_delete(ng_color_t** selfp)
{
  free(*selfp);
  *selfp = 0x0;
}


// compare structs -- suitable for use in sorting
// returns  <0 iff c1 < c2
//           0 iff c1 ==c2
//          >0 iff c1 > c2
int ng_color_compare(const ng_color_t* c1,
		     const ng_color_t* c2)
{
  const int cmp1 = c1->state_ - c2->state_;
  if(0==cmp1){
    const int cmp2 = c1->delta_ - c2->delta_;
    return cmp2;
  }
  return cmp1;
}

  
// debugging
void ng_color_dump(const ng_color_t* self)
{
  printf("color state=%d  delta = %d\n", 
	 self->state_,
	 self->delta_);
}

