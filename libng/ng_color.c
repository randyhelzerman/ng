#include <ng_color.h>

#include<stdlib.h>

// create a new color
ng_color_t* ng_color_new(const int state, const int delta)
{
  ng_color_t* self = (ng_color_t*)malloc(sizeof(ng_color_t));
  ng_color_init(self, state, delta);
  return self;
}

ng_color_t* ng_color_init(ng_color_t* self,
			  const int state, const int delta)
{
  self->state_ = state;
  self->delta_ = delta;
  return self;
}
  
ng_color_t* ng_color_cp_init(const ng_color_t* self,ng_color_t* tgt)
{
  tgt->state_ = self->state_;
  tgt->delta_ = self->delta_;
  return tgt;
}


void ng_color_delete(ng_color_t** selfp)
{
  free(*selfp);
  *selfp = 0x0;
}


// not really necessary, just incase we want to
void ng_color_deinit(ng_color_t* self)
{
  self->state_ = 0xdeadbeef;
  self->delta_ = 0xdeadbeef;
}


ng_color_t* ng_color_cp(const ng_color_t* self, ng_color_t* tgt)
{
  return ng_color_cp_init(self,tgt);
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


bool ng_color_equal(const ng_color_t* c1,
		    const ng_color_t* c2)
{
  return (c1->state_ == c2->state_) && (c1->delta_ == c2->delta_);
}

