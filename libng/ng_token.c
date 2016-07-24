#include <ng_token.h>

#include<string.h>
#include<stdlib.h>

// construction
ng_token*
ng_token_new(const char* begin,
	     const char* end,
	     const long int type)
{
  ng_token*  self
    = (ng_token*)malloc(sizeof(ng_token));
  
  return ng_token_init(self, begin, end, type);
}


ng_token*
ng_token_init(ng_token* self,
	      const char* begin,
	      const char* end,
	      const long int type)
{
  self->begin_ = begin;
  self->end_   = end;
  self->type_  = type;
  
  return self;
}


// destruction
void ng_token_delete(ng_token** selfp)
{
  ng_token_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_token_uninit(ng_token* self)
{
  self->begin_ = 0x0;
  self->end_ = 0x0;
}
  

//-------
// access
//-------


int ng_token_strlen(const ng_token* self)
{
  // The number of chars in the range, plus 1 for the 0x0 terminator
  return 1 + (self->end_ - self->begin_);
}




