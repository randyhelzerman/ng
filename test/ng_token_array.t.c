#include <ng_token_array.h>
#include <ng_token_array.t.h>

#include <ng_token.h>
#include <ng_token.t.h>

#include <ng_vector.h>

// debugging

void ng_token_array_dump(const ng_token_array_t* self)
{
  for(int i=0;i<self->tokens_->numb_;i++){
    ng_token_dump(ng_vector_at(self->tokens_,
			       i,
			       sizeof(ng_token_t)));
  }
}
