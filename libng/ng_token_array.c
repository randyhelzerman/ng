#include <ng_token_array.h>

#include<stdlib.h>

#include <ng_vector.h>
#include <ng_token.h>


// construction
ng_token_array_t* ng_token_array_new()
{
  ng_token_array_t* self
    = (ng_token_array_t*)malloc(sizeof(ng_token_array_t));
  
  return ng_token_array_init(self);
}


ng_token_array_t* ng_token_array_init(ng_token_array_t* self)
{
  self->tokens_ = ng_vector_new(sizeof(ng_token_t), 10);
  self->string_ = 0x0;
  
  return self;
}

  
// destruction
void ng_token_array_delete(ng_token_array_t** selfp)
{
  // make it ok to delete a null pointer to one of thse
  if(0x0==*selfp) return;
  
  ng_token_array_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_token_array_uninit(ng_token_array_t* self)
{
  ng_vector_delete(&self->tokens_,
		   sizeof(ng_token_t),
		   (void(*)(void*))ng_token_uninit);
}


// accesss
  
void ng_token_array_set_string(ng_token_array_t* self,
			       const char* string)
{
  self->string_ = string;
}


void ng_token_array_push_back(ng_token_array_t* self,
			      const char* begin,
			      const char* end,
			      const long int type)
{
  // entry to be added
  ng_token_t entry;
  ng_token_init(&entry,
			    begin,
			    end,
			    type);
  
  // push it back.  Since it can be bitcopied
  // and doesn't need a destructor, we can just
  // pass nulls in for the functions
  ng_vector_push_back(&self->tokens_,
		      sizeof(ng_token_t),
		      &entry,
		      0x0,0x0);
}
