#include <ng_symbol_table_entry.h>
#include <ng_symbol_table_entry.t.h>


// debugging
void ng_symbol_table_entry_dump(const ng_symbol_table_entry_t* self)
{
  printf("%10s : type=%5ld : id=%2d\n",
	 self->name_,
	 self->type_,
	 self->id_);
}
  
