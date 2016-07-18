#include <ng_color.h>
#include <ng_color.t.h>

#include<stdio.h>

// debugging
void ng_color_dump(const ng_color_t* self)
{
  printf("color(state=%d,delta=%d)  ", 
	 self->state_,
	 self->delta_);
}

