#include <ng_nfa_factory.h>

#include <ng_ascii_util.h>
#include <ng_token_array.h>
#include <ng_symbol_table.h>

#include <string.h>
#include <stdlib.h>


// construction
ng_nfa_factory_t* ng_nfa_factory_new()
{
  // allocate sufficient memory
  ng_nfa_factory_t* self
    = (ng_nfa_factory_t*)malloc(sizeof(ng_nfa_factory_t));
  
  // initialize it
  return ng_nfa_factory_init(self);
}


ng_nfa_factory_t* ng_nfa_factory_init(ng_nfa_factory_t* self)
{
  self->tokens_ = 0x0;
  self->symbol_table_ = ng_symbol_table_new();
  
  return self;
}


// deletion
void ng_nfa_factory_delete(ng_nfa_factory_t** selfp)
{
  // make it ok to delete a null pointer to one of thse
  if(0x0==*selfp) return;
  
  ng_nfa_factory_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_nfa_factory_uninit(ng_nfa_factory_t* self)
{
  ng_token_array_delete(&self->tokens_);
  ng_symbol_table_delete(&self->symbol_table_);
}


// access

// build an nfa from parsing the string spec
ng_nfa_t* ng_nfa_factory_build(ng_nfa_factory_t* self,
			       const char* string)
{
  return 0x0;
}
