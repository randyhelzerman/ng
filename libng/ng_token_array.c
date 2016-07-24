#include <ng_token_array.h>

#include<stdlib.h>

#include <ng_vector.h>
#include <ng_token.h>


// construction
ng_token_array* ng_token_array_new()
{
  ng_token_array* self
    = (ng_token_array*)malloc(sizeof(ng_token_array));
  
  return ng_token_array_init(self);
}


ng_token_array* ng_token_array_init(ng_token_array* self)
{
  self->tokens_ = ng_vector_new(sizeof(ng_token), 10);
  self->string_ = 0x0;
  
  return self;
}

  
// destruction
void ng_token_array_delete(ng_token_array** selfp)
{
  // make it ok to delete a null pointer to one of thse
  if(0x0==*selfp) return;
  
  ng_token_array_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_token_array_uninit(ng_token_array* self)
{
  ng_vector_delete(&self->tokens_,
		   sizeof(ng_token),
		   (void(*)(void*))ng_token_uninit);
}


// accesss


// return number of tokens in the array
size_t ng_token_array_size(const ng_token_array* self)
{
  return self->tokens_->numb_;
}


ng_token* ng_token_array_at(ng_token_array* self,
			       const size_t index)
{
  return ng_vector_at(self->tokens_,
		      index,
		      sizeof(ng_token));
}


void ng_token_array_set_string(ng_token_array* self,
			       const char* string)
{
  self->string_ = string;
}


void ng_token_array_push_back(ng_token_array* self,
			      const char* begin,
			      const char* end,
			      const long int type)
{
  // entry to be added
  ng_token entry;
  ng_token_init(&entry,
		begin,
		end,
		type);
  
  // push it back.  Since it can be bitcopied
  // and doesn't need a destructor, we can just
  // pass nulls in for the functions
  ng_vector_push_back(&self->tokens_,
		      sizeof(ng_token),
		      &entry,
		      0x0,0x0);
}
