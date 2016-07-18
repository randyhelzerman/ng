#include <ng_symbol_table.h>
#include <ng_symbol_table_entry.h>


// constructor
ng_symbol_table_t* ng_symbol_table_new()
{
  ng_symbol_table_t* self = (ng_symbol_table_t*)malloc(sizeof(ng_symbol_table_t));
  return ng_symbol_table_init(self);
}


ng_symbol_table_t* ng_symbol_table_init(ng_symbol_table_t* self)
{
  self->tree_ = ng_rb_tree_new();
  return self;
}

  
// destructor
void ng_symbol_table_delete(ng_symbol_table_t** selfp)
{
  ng_symbol_table_uninit(*selfp);
  free(*selfp);
  *selfp = 0x0;
}


void ng_symbol_table_uninit(ng_symbol_table_t* self)
{
  ng_rb_tree_delete(&self->tree_,
		    (void(*)(void*))ng_symbol_table_entry_uninit);
}


// access
int
ng_symbol_table_insert(ng_symbol_table_t* self,
		       const char* name,
		       const int type)
{
  // make a temporary entry to insert
  ng_symbol_table_entry_t* entry1
    = ng_symbol_table_entry_new(name, type);
  
  ng_symbol_table_entry_t* entry2 = 
    (ng_symbol_table_entry_t* )
    ng_rb_tree_insert(self->tree_,
		      ng_symbol_table_entry_size(entry1),
		      entry1,
		      (void*(*)(const void*,
				void*))ng_symbol_table_entry_cp_init,
		      (int(*)(const void*,
			      const void*))ng_symbol_table_entry_compare)->fruit_;
  
  // ensure that the entries are equal to each other
  bool returner
    = ng_symbol_table_entry_equal(entry1, entry2)
    ? 0
    : NG_SYMBOL_TABLE_WRONG_TYPE;
  
  // free memory of temporary entry
  ng_symbol_table_entry_delete(&entry1);
  
  return returner;
}


const ng_symbol_table_entry_t*
ng_symbol_table_lookup(ng_symbol_table_t* self,
		       const char* name)
{
  // make a temporary entry to look up
  ng_symbol_table_entry_t* entry1
    = ng_symbol_table_entry_new(name, 0);
  
  const ng_symbol_table_entry_t* entry2
    = ng_rb_tree_lookup(self->tree_,
			entry1,
			(int(*)(const void*,
				const void*))ng_symbol_table_entry_compare);
  
  // free memory of temporary entry
  ng_symbol_table_entry_delete(&entry1);
  
  return entry2;
}
