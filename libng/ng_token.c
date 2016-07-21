#include <ng_token.h>

#include<string.h>
#include<stdlib.h>

// construction
ng_token_t*
ng_token_new(const char* begin,
			 const char* end,
			 const long int type)
{
  ng_token_t*  self
    = (ng_token_t*)malloc(sizeof(ng_token_t));

  return ng_token_init(self, begin, end, type);
}

  
ng_token_t*
ng_token_init(ng_token_t* self,
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
void ng_token_delete(ng_token_t** selfp)
{
  ng_token_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_token_uninit(ng_token_t* self)
{
  self->begin_ = 0x0;
  self->end_ = 0x0;
}
  

//-------
// access
//-------


int ng_token_strlen(const ng_token_t* self)
{
  // The number of chars in the range, plus 1 for the 0x0 terminator
  return 1 + (self->end_ - self->begin_);
}


