#include <ng_nfa_factory.h>
#include <ng_nfa_factory.t.h>

#include<ng_token_array.t.h>
#include<ng_symbol_table.t.h>

#include <stdio.h>

void ng_nfa_factory_dump(ng_nfa_factory_t *self)
{
  printf("nfa factory\n");
  ng_token_array_dump(self->tokens_);
  ng_symbol_table_dump(self->symbol_table_);
}
