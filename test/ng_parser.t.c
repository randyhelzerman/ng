#include <ng_parser.h>
#include <ng_parser.t.h>

#include<ng_token_array.t.h>
#include<ng_symbol_table.t.h>

#include <stdio.h>


void ng_parser_dump(ng_parser *self)
{
  ng_token_array_dump(self->tokens_);
  ng_symbol_table_dump(self->symbol_table_);
}
