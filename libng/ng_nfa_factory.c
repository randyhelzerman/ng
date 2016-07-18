#include <ng_nfa_factory.h>

#include <ng_token_array.h>
#include <ng_symbol_table.h>

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
  self->tokens_ = ng_token_array_new();
  self->symbol_table_ = ng_symbol_table_new();
  
  return self;
}


// deletion
void ng_nfa_factory_delete(ng_nfa_factory_t** selfp)
{
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
ng_nfa_t* build(const char* string)
{
  return 0x0;
}
