#include <ng_symbol_table.h>
#include <ng_symbol_table.t.h>

#include<stdio.h>

#include <ng_symbol_table_entry.h>
#include <ng_symbol_table_entry.t.h>

#include<ng_rb_tree.h>

// debgugging
void ng_symbol_table_dump(const ng_symbol_table_t* self)
{
  printf("Symbol table:\n");
  ng_rb_tree_visit(self->tree_,
		   (void(*)(const void*))ng_symbol_table_entry_dump);
}
