#include <ng_symbol_table_entry.h>

#include<string.h>
#include<stdlib.h>

// construction
ng_symbol_table_entry_t *
ng_symbol_table_entry_new(const char* name,
			  const long int type)
{
  const size_t size = sizeof(ng_symbol_table_entry_t) + strlen(name);
  ng_symbol_table_entry_t *self = (ng_symbol_table_entry_t *)malloc(size);
  return ng_symbol_table_entry_init(self, name, type);
}


ng_symbol_table_entry_t *
ng_symbol_table_entry_init(ng_symbol_table_entry_t*self,
			   const char* name,
			   const long int type)
{
  self->type_ = type;
  self->id_ = 0;
  strcpy(self->name_, name);
  return self;
}


ng_symbol_table_entry_t*
ng_symbol_table_entry_cp_init(const ng_symbol_table_entry_t* src,
			      ng_symbol_table_entry_t* tgt)
{
  tgt->type_ = src->type_;
  tgt->id_   = src->id_;
  strcpy(tgt->name_, src->name_);
  
  return tgt;
}


// destruction
void ng_symbol_table_entry_delete(ng_symbol_table_entry_t **selfp)
{
  ng_symbol_table_entry_uninit(*selfp);
  free(*selfp);
  *selfp=0x0;
}


void ng_symbol_table_entry_uninit(ng_symbol_table_entry_t* self)
{
  self->type_=0;
  self->name_[0] = 0x0;
}

  
// access

// returns the real size this takes up.  Remember we have the
// expandy-array at the end of the struct.
size_t ng_symbol_table_entry_size(const ng_symbol_table_entry_t* self)
{
  const size_t size = sizeof(ng_symbol_table_entry_t) + strlen(self->name_);
  return size;
}


int ng_symbol_table_entry_compare(const ng_symbol_table_entry_t* e1,
				  const ng_symbol_table_entry_t* e2)
{
  const long int res = e1->type_ - e2->type_;
  if(0 != res) return res;
  
  return strcmp(e1->name_, e2->name_);
}


// returns true if the two entries are equal.  Note this doesn't
// have to be the same conditions under which the comparison
// function above returns zero, because we are using the rb
// tree as a map.
bool ng_symbol_table_entry_equal(const ng_symbol_table_entry_t* e1,
				 const ng_symbol_table_entry_t* e2)
{
  if(e1->type_ !=  e2->type_) return false;
  if(0 != strcmp(e1->name_, e2->name_)) return false;
  
  return true;
}
